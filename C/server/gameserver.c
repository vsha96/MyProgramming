#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <math.h>

int error_handler()
{
	perror(NULL);
	fflush(stderr);
	return 1;
}

#define INBUFSIZE 128
#define SESS_ARR_SIZE 16

int global_count = 0;

const int level_change[5][5] = {
	{ 4, 4, 2, 1, 1},
	{ 3, 4, 3, 1, 1},
	{ 1, 3, 4, 3, 1},
	{ 1, 1, 3, 4, 3},
	{ 1, 1, 2, 4, 4}
};

const float market_count[5][2] = {
	{ 1.0, 3.0},
	{ 1.5, 2.5},
	{ 2.0, 2.0},
	{ 2.5, 1.5},
	{ 3.0, 1.0}
};
const int market_price[5][2] = {
	{ 800, 6500},
	{ 650, 6000},
	{ 500, 5500},
	{ 400, 5000},
	{ 300, 4500}
};

char msg_intro[] =	"* Welcome to the game server\n* Type 'help' for command list\n";
char msg_warn[] = 	"* Unknown command! Type 'help' for commands\n";

enum fsm_states {
	fsm_start,
	fsm_wait_connection = fsm_start,
	fsm_command,
	fsm_end_turn,
	fsm_finish,
	fsm_close,
	fsm_error
};

struct session { /*equals player in bank*/
	int fd;
	unsigned long from_ip;
	unsigned short from_port;
	char buf[INBUFSIZE];
	int buf_used;
	enum fsm_states state;
	/*after end turn, we look in the bank: all players have done turn?*/
	/*for game: information about resources*/
	/* ? int status; */
	int number; /*number of player*/ /*depends on count of players*/
	int money; /* 10000 */ /*start count*/
	int material; /* 4 */
	int product; /* 2 */
	int factory; /* 2 */
	/*refreshable inf*/
	int max_product; /*in every month equals count of factories*/
	int request_auction; /*0 or 1*/
};

struct app_build {
	int month; /*every turn it decreases*/
	int sd; /*without search will come to the player*/
	struct app_build *next;
};

struct app_auction {
	int count;
	int price;
	int sd;
	struct app_auction *next;
};

struct bank_stat {
	struct session **player; /*equals sess_array in serv, it's same*/
	int turn;

	int market_level;
	int market_material;
	int market_material_price;
	int market_product;
	int market_product_price;

	int player_max_count; /*we wait for N players before the start*/
	int player_count;

	struct app_build *build;
	struct app_auction *auction;
};

struct bank_stat *bank;


/*void bank_setup(struct server_stat *serv, int max_player);*/
void bank_audit();
void bank_send_news_string(char*);
void bank_send_news_turn();
void bank_send_news_result();
void bank_send_news_finish();

void bank_check_count_player();
void bank_player_refresh_inf();
void bank_activate_player();
void bank_tax();

void bank_market_change();
void bank_calculate_market();

void bank_check_end_turn();
void bank_check_finish();

/*procedure*/
/*for game: send to all players news (what have just changed)*/

/*==========SESSION ACTIONS==========*/
void session_send_string(struct session *sess, const char *str)
{
	write(sess->fd, str, strlen(str));
}

void player_send_string(struct session *sess, const char *str)
{
	session_send_string(sess, str);
}

void session_send_int(struct session *sess, const int n)
{
	char send[256];
	sprintf(send, "%i", n);
	session_send_string(sess, send);
	session_send_string(sess, "\n");
}

void player_send_int(struct session *sess, const int n)
{
	session_send_int(sess, n);
}

void player_setup(int sd)
{
	bank->player_count += 1;
	bank->player[sd]->number = bank->player_count;
	bank->player[sd]->money = 10000;
	bank->player[sd]->material = 4;
	bank->player[sd]->product = 2;
	bank->player[sd]->factory = 2;
	/*refreshable inf TODO*/
	bank->player[sd]->max_product = 0;
	bank->player[sd]->request_auction = 0;
}

void player_send_info_about(struct session *sess, int tag)
{
	struct session *player, *target = NULL;
	int i = 0;
	for (i=0;i<SESS_ARR_SIZE;i++) {
		if (bank->player[i] && bank->player[i]->number == tag) {
			target = bank->player[i];
			break;
		}
	}
	player = sess;
	if (target) {
		player_send_string(player,"* Number:     \t");
		player_send_int(player, target->number);
		player_send_string(player,"* Money:      \t");
		player_send_int(player, target->money);
		player_send_string(player,"* Material:   \t");
		player_send_int(player, target->material);
		player_send_string(player,"* Product:    \t");
		player_send_int(player, target->product);
		player_send_string(player,"* Factory:    \t");
		player_send_int(player, target->factory);
	
		/* // DEBUG
		player_send_string(player,"* MAX PROD:    \t");
		player_send_int(player, target->max_product);
		*/

	} else {	
		player_send_string(player,"* No player ");
		player_send_int(player, tag);
	}
}

void player_send_market(struct session *player)
{
	player_send_string(player, "* market level   = ");
	player_send_int(player, bank->market_level + 1);
	player_send_string(player, "* material count = ");
	player_send_int(player, bank->market_material);
	player_send_string(player, "*        1 item ~ $");
	player_send_int(player, bank->market_material_price);
	player_send_string(player, "* product count  = ");
	player_send_int(player, bank->market_product);
	player_send_string(player, "*        1 item ~ $");
	player_send_int(player, bank->market_product_price);
}

void player_send_help(struct session *player)
{
	player_send_string(player,"* me\n");
	player_send_string(player,"\t- just your info\n");
	player_send_string(player,"* player <number>\n");
	player_send_string(player,"\t- receive inf about player\n");
	player_send_string(player,"* turn\n");
	player_send_string(player,"\t- end your turn\n");
	player_send_string(player,"* market\n");
	player_send_string(player,"\t- receive inf about market state\n");
	player_send_string(player,"* build <count>\n");
	player_send_string(player,"\t- request factories\n");
	player_send_string(player,"* prod <count>\n");
	player_send_string(player,"\t- make production\n");
	player_send_string(player,"* buy <count> <price>\n");
	player_send_string(player,"\t- buy material\n");
	player_send_string(player,"* sell <count> <price>\n");
	player_send_string(player,"\t- sell production\n");
}

void bank_build_print()
{ /*TODO*/ /*DEBUG*/
	struct app_build *temp;
	temp = bank->build;
	while(temp) {
		printf("[m:%i sd:%i]",temp->month,temp->sd);
		temp = temp->next; 
	}
	printf("\n");
}

void player_request_build(struct session *player)
{
	struct app_build **app;
	app = malloc(sizeof(struct app_build*));
	*app = bank->build;
	while (app[0] && app[0]->next) {
		app[0]++;
	}
	app[0]->next = malloc(sizeof(struct app_build));
	app[0] = app[0]->next;
	app[0]->month = 4;
	app[0]->sd = player->fd;
	app[0]->next = NULL;
	/*TODO*/
	bank_build_print();
}

struct session *session_make_new(int fd, struct sockaddr_in *from)
{
	struct session *sess = malloc(sizeof(*sess));
	sess->fd = fd;
	sess->from_ip = ntohl(from->sin_addr.s_addr);
	sess->from_port = ntohs(from->sin_port);
	sess->buf_used = 0;
	sess->state = fsm_start;

	session_send_string(sess, msg_intro); 
	/*for game: setup information about resources*/
		/*SOLVED in accept_client*/
	return sess;
}

/*=====support for handle=====*/
int word_count(char *line)
{
	int size = 0;
	char temp[INBUFSIZE], *word, *sep = " ";
	strcpy(temp, line);
	for(word = strtok(temp, sep);
		word;
		word = strtok(NULL, sep))
		size++;
	return size;
}

void packline_print(char **packline)
{
	char **temp = packline;
	printf("packline_print:");
	while(temp[0]) {
		printf("[%s]", temp[0]);
		temp++;
	}
	printf("\n");
}

int packline_size(char **packline)
{
	char **temp = packline;
	int size = 0;
	while(temp[0]) {
		size++;
		temp++;
	}
	return size;
}

char **session_handle_packline(const char *line)
{
	char **packline;
    char temp[INBUFSIZE], *word, *sep = " ";
    int i = 0, size;
    size = word_count((char*)line);
    packline = malloc((size+1)*sizeof(char*));
    packline[size] = NULL;

    strcpy(temp, line);
    for (word = strtok(temp, sep);
        word;
        word = strtok(NULL, sep))
	{
		packline[i] = word;
		i++;
	}
    /* DEBUG */ //packline_print(packline);
    return packline;
}
/*=====end support for handle=====*/

/*=====COMMAND HANDLERS=====*/
int handler_command_1(struct session *player, char **cmd)
{
	/* DEBUG */
	if(!strcmp("finish", cmd[0])) {
		player_send_string(player, "* cmd: FINISH\n");
		player->state = fsm_finish;
		return 1;
	}

	if (!strcmp("me", cmd[0])) {
		player_send_info_about(player, player->number);
	} else if (!strcmp("market", cmd[0])) {
		player_send_market(player);
	} else if (!strcmp("turn", cmd[0])) {
		/* DEBUG */ //printf("PLAYER[%i]: end_turn\n", player->number);
		player->state = fsm_end_turn;
		player_send_string(player, "* you end turn\n");
	} else if (!strcmp("help", cmd[0])) {
		player_send_help(player);
	} else {
		player_send_string(player, msg_warn);
		return 0;
	}
	return 1;
}

int handler_command_2(struct session *player, char **cmd)
{
	char *endptr;
	int number = strtol(cmd[1], &endptr, 10);
	if (*endptr) {
		session_send_string(player, msg_warn);
		return 0;
	}

	if (!strcmp("player", cmd[0])) {
		player_send_info_about(player, number);
	} else if (!strcmp("prod", cmd[0])) {
		if (player->money < 2000*number) {
			player_send_string(player, "* not enough money\n");
		} else if (player->max_product < number) {
			player_send_string(player, "* not enough factories\n");
		} else {
			player->money -= 2000*number;
			player->material -= number;
			player->max_product -= number;
			player_send_string(player, "* - $");
			player_send_int(player, 2000*number);
			player->product += number;
		}
	} else if (!strcmp("build", cmd[0])) {
		player_send_string(player, "* cmd: build <count>\n");
		/*request for factory with turn of creation*/
		player_request_build(player);
		/*bank looks to the list of requests and builds if it's time*/
		/*TODO*/
	} else {
		session_send_string(player, msg_warn);
		return 0;
	}
	return 1;
}

int handler_command_3(struct session *player, char **cmd)
{
	char *endptr1, *endptr2;
	int count = strtol(cmd[1], &endptr1, 10);
	int price = strtol(cmd[2], &endptr2, 10);
	if (*endptr1 || *endptr2) {
		session_send_string(player, msg_warn);
		return 0;
	}

	if (!strcmp("buy", cmd[0])) {
		player_send_string(player, "* cmd: buy <count> <price>\n");
		/* TODO */
	} else if (!strcmp("sell", cmd[0])) {
		player_send_string(player, "* cmd: sell <count> <price>\n");
		/* TODO */
	} else {
		session_send_string(player, msg_warn);
		return 0;
	}
	return 1;
}
/*=====END OF COMMAND HANDLERS=====*/

void session_handle_command(struct session *sess, const char *line)
{
	char **cmd;
	int size;
	/* DEBUG */ //printf("PLAYER[%i]:", sess->number);
	/* DEBUG */ //printf(" handle_command: \n\t");
	cmd = session_handle_packline(line);
	size = packline_size(cmd);
	
	if (size == 1) {
		handler_command_1(sess, cmd);
	} else if (size == 2) {
		handler_command_2(sess, cmd);
	} else if (size == 3) {
		handler_command_3(sess, cmd);
	} else {
		if (*cmd)
			session_send_string(sess, msg_warn);
	}
	
	/* smt for change resources*/
}

void session_fsm_step(struct session *sess, char *line)
{
	switch(sess->state)
	{
		case fsm_wait_connection:
			session_send_string(sess, "* waiting other players\n");
			break;
		case fsm_command:
			session_handle_command(sess, line);

			bank_audit();
			bank_check_end_turn();
			//bank_check_finish();

			free(line);
			break;
		/* for game: */
		case fsm_end_turn:
			break;
		/* somewhere must be procedure for check 'are all users end?' */
		case fsm_finish:
			/* smt will point end of the game... */
		case fsm_close:
		case fsm_error:
			free(line);
	}
}

void session_check_lf(struct session *sess)
{
	int i, pos = -1;
	char *line;
	for (i=0; i < sess->buf_used; i++)
	{
		if (sess->buf[i] == '\n')
		{
			pos = i;
			break;
		}
	}
	if (pos == -1)
		return;

	line = malloc(pos+1);
	memcpy(line, sess->buf, pos);
	line[pos] = 0;
	memmove(sess->buf, sess->buf+pos, pos+1);
	sess->buf_used -= (pos+1);

	if (line[pos-1] == '\r')
		line[pos-1] = 0;

	/*DEBUG*/ /*printf("check_lf: [%s]\n", line);*/
	session_fsm_step(sess, line);
}

int session_read(struct session *sess)
{
	int rr, bufp = sess->buf_used;
	rr = read(sess->fd, sess->buf + bufp, INBUFSIZE - bufp);
	if (rr < 0)
	{
		sess->state = fsm_error;
		return 0;
	}
	if (rr == 0)
	{
		sess->state = fsm_close;
	}
	sess->buf_used += rr;
	session_check_lf(sess);
	if (sess->buf_used >= INBUFSIZE)
	{
		session_send_string(sess, "Line too long! Goodbye...\n");
		sess->state = fsm_error;
		return 0;
	}
	if (sess->state == fsm_close)
		return 0;
	return 1;
}

void session_cleanup(struct session *sess)
{
	/*may be useful*/
}

/*==========SERVER SETUP AND RUN==========*/
struct server_stat {
	int ls;
	struct session **sess_array; /* depends of SESS_ARR_SIZE */
	/* is game started? than new connection will be 'watcher'*/
	/* step of the game - ?enum round?*/
	int sess_array_size;
};

/*==========BANK ACTIONS==========*/
void bank_audit()
{
	int i;
	printf("***BANK AUDIT***\n");
	printf("*turn         \t%i\n",bank->turn);

	printf("*market       \t%i\n",bank->market_level+1);
	printf("*market_mat   \t[%i]\t%i$\n",
						bank->market_material,
						bank->market_material_price);
	printf("*market_prod  \t[%i]\t%i$\n",
						bank->market_product,
						bank->market_product_price);

	printf("*max players: \t%i\n",bank->player_max_count);
	printf("*player_count:\t%i\n",bank->player_count);
	for (i=4;i < 4 + bank->player_max_count;i++) {
		if (bank->player[i]) {
			printf("*\tplayer %i [%i]\t%i$\t",i,
								bank->player[i]->number,
								bank->player[i]->money);
			if (bank->player[i]->state == fsm_wait_connection) {
				printf("waiting\n");
			} else if (bank->player[i]->state == fsm_command) {
				printf("active\n");
			} else if (bank->player[i]->state == fsm_end_turn) {
				printf("end turn\n");
			} else if (bank->player[i]->state == fsm_finish) {
				printf("finish\n");
			}
		} else {
			printf("*\tplayer NULL\n");
		}
	}
}

void bank_send_news_string(char *line)
{
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->player[i]) {
			player_send_string(bank->player[i], line);
		}
	}
}

void bank_send_news_turn()
{
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->player[i]) {
			player_send_string(bank->player[i], "* MONTH ");
			player_send_int(bank->player[i], bank->turn);
		}
	}
}

void bank_send_news_result()
{
	/*TODO*/
}

void bank_send_news_finish()
{
	int i, winner = -1;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->player[i]) {
			player_send_string(bank->player[i], "* GAME OVER \n");
			if (bank->player[i]->state != fsm_finish) {
				winner = i;
				bank->player[winner]->state = fsm_finish;
			}
		}
	}
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->player[i]) {
			if (winner != -1) {
				player_send_string(bank->player[i], "* WINNER - PLAYER ");
				player_send_int(bank->player[i],
									bank->player[winner]->number);
			} else {
				player_send_string(bank->player[i], "* WINNER - NOBODY ");
			}
		}
	}
}

void bank_check_count_player()
{
	int i;
	if (bank->player_count == bank->player_max_count) {
		for (i=0;i < SESS_ARR_SIZE;i++) {
			if	(bank->player[i]) {
				bank->player[i]->state = fsm_command;
			}
		}
		/* DEBUG */ printf("=====GAME START=====\n");

		bank_send_news_string("* GAME STARTS\n");
		bank->turn += 1;

		bank_player_refresh_inf();

	}
}

void bank_player_refresh_inf()
{
	/*TODO TODO TODO*/
	struct session *player;
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		player = bank->player[i];
		if	(player &&
			player->state != fsm_finish) {
			player->max_product = player->factory;
			player->request_auction = 0;
		}
	}
}

void bank_activate_player()
{
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if	(bank->player[i] &&
			bank->player[i]->state != fsm_finish) {
			bank->player[i]->state = fsm_command;
		}
	}
}

void bank_tax()
{
	struct session* player;
	int i, total;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if	(bank->player[i] &&
				bank->player[i]->state != fsm_finish) {
			player = bank->player[i];
			total = 0;
			player->money -=  300*player->material; /* total += tax */
			total += 300*player->material;
			player->money -=  500*player->product;
			total += 500*player->product;
			player->money -= 1000*player->factory;
			total += 1000*player->factory;
			player_send_string(player, "* taxes: - $");
			player_send_int(player, total);
		}
	}
}

void bank_check_money()
{
	/* put this in fsm_command , to tell 'you are bankrot'*/
	/* and in check_end_turn */
	/* if money < 0 -> player->state=fsm_finish*/
	/* TODO */
	struct session* player;
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if	(bank->player[i] &&
			bank->player[i]->state != fsm_finish) {
			player = bank->player[i];
			if (player->money < 0) {
				/* DEBUG*/
					printf("BANK: player %i BANKRUPT\n", player->number);
				player->state = fsm_finish;
				player_send_string(player, "* you lost\n");
			}
		}
	}
}

void bank_market_change()
{
	int i = 0, s = 0;
	int r = 1 + (int)(12.0*rand()/(RAND_MAX+1.0));
	while (s < r) {
		s += level_change[bank->market_level][i];
		i++;
	}
	/* 1 <= i <= 5*/
	i--;
	bank->market_level = i;
	/* DEBUG */ printf("BANK: market_change: %i\n", i);
}

void bank_calculate_market()
{
	int i, count = 0;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if	(bank->player[i] &&
			bank->player[i]->state != fsm_finish) {
			count += 1;
		}
	}
	bank->market_material=(int)(count * 
								market_count[bank->market_level][0]);
	bank->market_material_price = market_price[bank->market_level][0];
	bank->market_product=(int)(count *
								market_count[bank->market_level][1]);
	bank->market_product_price = market_price[bank->market_level][1];
}

void bank_check_end_turn()
{
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if	(bank->player[i] &&
			bank->player[i]->state != fsm_end_turn &&
			bank->player[i]->state != fsm_finish) {
			/*DEBUG*/ //printf("BANK: there are active players\n");
			break;
		}
	}
	if (i == SESS_ARR_SIZE) {
		/*DEBUG*/ //printf("BANK: there are NO active players\n");
		/*TODO TODO TODO*/
		/*handle requests for auction*/
		/*handle requests for buildings*/
		/*refresh players inf*/
		bank->turn += 1;
		printf("=====TURN %i=====\n", bank->turn);
		bank_send_news_turn();

		bank_market_change();
		bank_calculate_market();
		bank_tax();
		bank_check_money();
		bank_check_finish();
		
		bank_player_refresh_inf();

		bank_activate_player();
		bank_audit();

	}
}

void bank_check_finish()
{
	int i, count=0;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->player[i] && bank->player[i]->state == fsm_finish) {
			count++;
		}
	}
	if ((bank->player_max_count - count) == 1 || 
		(bank->player_max_count - count) == 0 ||
			bank->player_count == 1) {
		printf("=====GAME END=====\n");
		bank_send_news_finish();
	}
}

void bank_setup(struct server_stat *serv, int max_player)
{
	bank = malloc(sizeof(struct bank_stat));
	bank->turn = 0;
	bank->market_level = 2;
	bank->market_material = 0;
	bank->market_material_price = 0;
	bank->market_product = 0;
	bank->market_product_price = 0;

	bank->player = serv->sess_array;
	bank->player_max_count = max_player;
	bank->player_count = 0;
	
	bank->build = NULL;
	bank->auction = NULL;

	bank_audit();
}
/*==========END OF BANK ACTIONS==========*/

int server_setup(struct server_stat *serv, int port, int max_player)
{
	int i;
	struct sockaddr_in addr;

	serv->ls = socket(AF_INET, SOCK_STREAM, 0);
	if (serv->ls == -1)
		return error_handler();

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if (-1 == bind(serv->ls, (struct sockaddr*)&addr, sizeof(addr)))
		return error_handler();
	if (-1 == listen(serv->ls, 16))
		return error_handler();
	
	/*there may be more parameters, if we change struct server_stat*/
	serv->sess_array = malloc(SESS_ARR_SIZE * sizeof(*serv->sess_array));
	serv->sess_array_size = SESS_ARR_SIZE;
	for(i=0; i < SESS_ARR_SIZE; i++)
		serv->sess_array[i] = NULL;
	/*make the global bank*/
	bank_setup(serv, max_player);
	return 0;
}

void server_accept_client(struct server_stat *serv)
{
	int sd;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	sd = accept(serv->ls, (struct sockaddr*) &addr, &len);
	if (sd >= SESS_ARR_SIZE)
	{
		printf("warning: count of ready to connect > SESS_ARR_SIZE\n");
		return;
	}
	/* DEBUG */ printf("SERVER: accept_client: %i\n", sd);
	if (sd == -1)
	{
		perror("accept");
		return;
	}
	serv->sess_array[sd] = session_make_new(sd, &addr);

	player_setup(sd);
	/* BANK */
	bank_check_count_player();
	bank_calculate_market();
	bank_audit();
}

void server_session_close(struct server_stat *serv, int sd)
{
	/* DEBUG */ printf("SERVER: session_close: %i\n", sd);
	close(sd);
	serv->sess_array[sd]->fd = -1;
	session_cleanup(serv->sess_array[sd]);
	free(serv->sess_array[sd]);
	serv->sess_array[sd] = NULL;

	bank->player_count -= 1;
}

int server_run(struct server_stat *serv)
{
	fd_set readfds /*writefds*/;
	int i, ssr, maxfd;
	for(;;)
	{
		maxfd = serv->ls;
		FD_ZERO(&readfds);
		/*FD_ZERO(&writefds);*/
		FD_SET(maxfd, &readfds);
		for (i=0; i < serv->sess_array_size; i++)
		{
			if (serv->sess_array[i])
			{
				FD_SET(i, &readfds);
				if (i > maxfd)
					maxfd = i;
			}
		}

		if (-1 == select(maxfd+1, &readfds, NULL, NULL, NULL))
		{
			perror("select");
			return 1;
		}

		if (FD_ISSET(serv->ls, &readfds))
			server_accept_client(serv);
			/* make a struct for gamer via global bank */

		for (i=0; i < serv->sess_array_size; i++)
		{
			int old_global_count = global_count, j; /* for news */
			if (serv->sess_array[i] && FD_ISSET(i, &readfds))
			{
				printf("SERVER: call: session_read: %i\n", i);
				ssr = session_read(serv->sess_array[i]);
				if (old_global_count != global_count) /* for news */
					j = i;
				if (!ssr)
					server_session_close(serv, i);
			}
			/*send news*/
			if (old_global_count != global_count)
			{
				for (i=0; i < serv->sess_array_size; i++)
				{	
					if (serv->sess_array[i] && i != j)
					{
						session_send_string
							(serv->sess_array[i], 
								"Value have changed\n");	
						session_send_int
							(serv->sess_array[i],
								global_count);
					}
				}
			}
			
			/*sent news*/
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	struct server_stat serv;
	//struct bank_stat bank;
	int port, max_player;
	char *endptr;

	if (argc != 3) {
        printf("Usage: ./server <port> <number of players>\n");
        return 1;
    }

	port = strtol(argv[1], &endptr, 10);
	if (*endptr) {
		printf("error: wrong port\n");
		return 1;
	}

	max_player = strtol(argv[2], &endptr, 10);
	if (*endptr || max_player > SESS_ARR_SIZE) {
		printf("error: wrong number of players (max = %i)\n",
				SESS_ARR_SIZE);
		return 1;
	}
	
	/*there we alse have setup for bank*/
	if (server_setup(&serv, port, max_player)) 
		return 1;

	server_run(&serv);
	return 0;
}
