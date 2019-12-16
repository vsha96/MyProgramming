#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

int error_handler()
{
	perror(NULL);
	fflush(stderr);
	return 1;
}

#define INBUFSIZE 1024
#define SESS_ARR_SIZE 16

const int level_change[5][5] = {
	{ 4, 4, 2, 1, 1},
	{ 3, 4, 3, 1, 1},
	{ 1, 3, 4, 3, 1},
	{ 1, 1, 3, 4, 3},
	{ 1, 1, 2, 4, 4}
};

const float m_count[5][2] = {
	{ 1.0, 3.0},
	{ 1.5, 2.5},
	{ 2.0, 2.0},
	{ 2.5, 1.5},
	{ 3.0, 1.0}
};
const int m_price[5][2] = {
	{ 800, 6500},
	{ 650, 6000},
	{ 500, 5500},
	{ 400, 5000},
	{ 300, 4500}
};

char msg_intro[] =
	"* Welcome to the game server\n* Type 'help' for command list\n";
char msg_warn[] =
	"* Unknown command! Type 'help' for commands\n";

enum fsm_states {
	fsm_start,
	fsm_wait = fsm_start,
	fsm_command,
	fsm_end_turn,
	fsm_finish,
	fsm_close,
	fsm_error
};

struct session { /*equals plr in bank*/
	int fd;
	unsigned long from_ip;
	unsigned short from_port;
	char buf[INBUFSIZE];
	int buf_used;
	enum fsm_states state;
	/*for game: information about resources*/
	int num; /*num of plr*/ /*depends on count of plrs*/
	int money; /* 10000 */ /*start count*/
	int material; /* 4 */
	int product; /* 2 */
	int factory; /* 2 */
	/*refreshable inf*/
	int max_product; /*in every month equals count of factories*/
	int app_buy; /*0 or 1*/
	int app_sell; /*0 or 1*/
};

struct app_build {
	int month; /*every turn it decreases*/
	int sd; /*without search will come to the plr*/
	struct app_build *next;
};

struct app_auc {
	int count;
	int price;
	int sd;
};

struct bank_stat {
	struct session **plr; /*equals sess_array in serv*/
	int turn;

	int m_level;
	int m_material;
	int m_material_price;
	int m_product;
	int m_product_price;

	int plr_max_count; /*we wait for N plrs before start*/
	int plr_count;

	struct app_build *build;
	struct app_auc auc_buy[SESS_ARR_SIZE][1];
	struct app_auc auc_sell[SESS_ARR_SIZE][1];
};

struct bank_stat *bank;

/*void bank_setup(struct server_stat *serv, int max_plr);*/
void bank_audit();
void bank_news_string(char*);
void bank_news_int(int);
void bank_news_turn();
void bank_news_finish();

void bank_check_count_plr();
void bank_plr_refresh_inf();
void bank_activate_plr();
void bank_tax();

void bank_m_change();
void bank_calculate_market();

void bank_check_end_turn();
void bank_check_finish();

void bank_handle_build();

void bank_handle_auc_buy();
void bank_handle_auc_sell();
void bank_auc_print();
void bank_auc_delete();
/*procedure*/
/*for game: send to all plrs news (what have just changed)*/

/*==========SESSION ACTIONS==========*/
void sess_send_string(struct session *sess, const char *str)
{
	write(sess->fd, str, strlen(str));
}

void plr_send_string(struct session *sess, const char *str)
{
	sess_send_string(sess, str);
}

void sess_send_int(struct session *sess, const int n)
{
	char send[256];
	sprintf(send, "%i", n);
	sess_send_string(sess, send);
	sess_send_string(sess, "\n");
}

void plr_send_int(struct session *sess, const int n)
{
	sess_send_int(sess, n);
}

void plr_send_help(struct session *plr);

void plr_setup(int sd)
{
	bank->plr_count += 1;
	bank->plr[sd]->num = bank->plr_count;
	bank->plr[sd]->money = 10000;
	bank->plr[sd]->material = 4;
	bank->plr[sd]->product = 2;
	bank->plr[sd]->factory = 2;
	/*refreshable inf*/
	bank->plr[sd]->max_product = 0;
	bank->plr[sd]->app_buy = 0;
	bank->plr[sd]->app_sell = 0;

	plr_send_help(bank->plr[sd]);
}

void plr_send_info_about(struct session *sess, int tag)
{
	struct session *plr, *target = NULL;
	int i = 0;
	for (i=0;i<SESS_ARR_SIZE;i++) {
		if (bank->plr[i] && bank->plr[i]->num == tag) {
			target = bank->plr[i];
			break;
		}
	}
	plr = sess;
	if (target) {
		plr_send_string(plr,"* Number:     \t");
		plr_send_int(plr, target->num);
		plr_send_string(plr,"* Money:     \t$");
		plr_send_int(plr, target->money);
		plr_send_string(plr,"* Material:   \t");
		plr_send_int(plr, target->material);
		plr_send_string(plr,"* Product:    \t");
		plr_send_int(plr, target->product);
		plr_send_string(plr,"* Factory:    \t");
		plr_send_int(plr, target->factory);
	
		/* // DEBUG
		plr_send_string(plr,"* MAX PROD:    \t");
		plr_send_int(plr, target->max_product);
		*/

	} else {	
		plr_send_string(plr,"* No plr ");
		plr_send_int(plr, tag);
	}
}
void plr_send_stat(struct session *plr)
{
	int i;
	plr_send_string(plr, "* ===PLAYERS INFO=== \n");
	for (i=0;i<SESS_ARR_SIZE;i++) {
		if (bank->plr[i] && 
			bank->plr[i]->num != plr->num) {	
			plr_send_string(plr, "* =PLAYER= ");
			plr_send_int(plr, bank->plr[i]->num);
			plr_send_info_about(plr, bank->plr[i]->num);
		}
	}
	plr_send_string(plr, "* ===END OF PLAYERS=== \n");
}

void plr_send_market(struct session *plr)
{
	plr_send_string(plr, "* market level   = ");
	plr_send_int(plr, bank->m_level + 1);
	plr_send_string(plr, "* material count = ");
	plr_send_int(plr, bank->m_material);
	plr_send_string(plr, "*        1 item price >= $");
	plr_send_int(plr, bank->m_material_price);
	plr_send_string(plr, "* product count  = ");
	plr_send_int(plr, bank->m_product);
	plr_send_string(plr, "*        1 item price <= $");
	plr_send_int(plr, bank->m_product_price);
}

void plr_send_help(struct session *plr)
{
	plr_send_string(plr,"* me\n");
	plr_send_string(plr,"\t- just your info\n");
	plr_send_string(plr,"* plr\n");
	plr_send_string(plr,"\t- all plrs stat\n");
	plr_send_string(plr,"* plr <num>\n");
	plr_send_string(plr,"\t- receive inf about plr\n");
	plr_send_string(plr,"* turn\n");
	plr_send_string(plr,"\t- end your turn\n");
	plr_send_string(plr,"* market\n");
	plr_send_string(plr,"\t- receive inf about market state\n");
	plr_send_string(plr,"* build <count>\n");
	plr_send_string(plr,"\t- request factories\n");
	plr_send_string(plr,"* prod <count>\n");
	plr_send_string(plr,"\t- make production\n");
	plr_send_string(plr,"* buy <count> <price>\n");
	plr_send_string(plr,"\t- buy material\n");
	plr_send_string(plr,"* sell <count> <price>\n");
	plr_send_string(plr,"\t- sell production\n");
}

void bank_build_print()
{ /*DEBUG*/
	struct app_build *temp;
	temp = bank->build;
	printf("REQ_BUILD:");
	while(temp) {
		printf("[m:%i sd:%i]",temp->month,temp->sd);
		temp = temp->next; 
	}
	printf("\n");
}

void plr_request_build(struct session *plr)
{
	struct app_build *app, *current = bank->build;
	app = malloc(sizeof(*app));
	app->month = 4;
	app->sd = plr->fd;
	app->next = NULL;
	if (current == NULL) {
		bank->build = app;
	} else {
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = app;
	}
}

void plr_app_buy(int count, int price, struct session* plr)
{
	int sd = plr->fd;
	if (plr->app_buy == 1) {
		plr_send_string(plr, "* you've sent app for material\n");
	} else if (count < 0) {
		plr_send_string(plr, "* invalid count\n");
	} else if (count > bank->m_material) {
		plr_send_string(plr, "* count > material of market\n");
	} else if (price < bank->m_material_price) {
		plr_send_string(plr, "* price < min price of material\n");
	} else {
		plr_send_string(plr, "* submited\n");
		plr->app_buy = 1;
		bank->auc_buy[sd]->count = count;
		bank->auc_buy[sd]->price = price;
		bank->auc_buy[sd]->sd = sd;
	}
}

void plr_app_sell(int count, int price, struct session* plr)
{
	int sd = plr->fd;
	if (plr->app_sell == 1) {
		plr_send_string(plr, "* you've sent app for product\n");
	} else if (count < 0) {
		plr_send_string(plr, "* invalid count\n");
	} else if (plr->product < count) {
		plr_send_string(plr, "* not enough product\n");
	} else if (count > bank->m_product) {
		plr_send_string(plr, "* count > product of market\n");
	} else if (price > bank->m_product_price) {
		plr_send_string(plr, "* price > max price of product\n");
	} else {
		plr_send_string(plr, "* submited\n");
		plr->app_sell = 1;
		bank->auc_sell[sd]->count = count;
		bank->auc_sell[sd]->price = price;
		bank->auc_sell[sd]->sd = sd;
	}
}

struct session *sess_make_new(int fd, struct sockaddr_in *from)
{
	struct session *sess = malloc(sizeof(*sess));
	sess->fd = fd;
	sess->from_ip = ntohl(from->sin_addr.s_addr);
	sess->from_port = ntohs(from->sin_port);
	sess->buf_used = 0;
	sess->state = fsm_start;

	sess_send_string(sess, msg_intro); 
	/*for game: setup information about resources*/
		/*SOLVED in accept_client*/
	return sess;
}

/*=====support for handle=====*/
int word_count(char *line)
{
	int size = 0;
	char t[INBUFSIZE], *w, *sep = " ";
	strcpy(t, line);
	for (w=strtok(t,sep);w;w=strtok(NULL, sep))
		size++;
	return size;
}

void packline_print(char **packline)
{
	int i=0;
	char **temp = packline;
	printf("packline_print:");
	while(temp[i]) {
		printf("[%s]", temp[i]);
		i++;
	}
	printf("\n");
}

int packline_size(char **packline)
{
	char **temp = packline;
	int i=0, size = 0;
	while(temp[i]) {
		size++;
		i++;
	}
	return size;
}

char **sess_handle_packline(const char *line)
{
	char **packline;
	char temp[INBUFSIZE], *word, *sep = " ";
	int i = 0, size;
	size = word_count((char*)line);
	packline = malloc((size+1)*sizeof(char*));
	packline[size] = NULL;

	strcpy(temp, line);
	for (word=strtok(temp, sep);word;word=strtok(NULL, sep))
	{
		packline[i] = word;
		i++;
	}
    /* DEBUG */ //packline_print(packline);
    return packline;
}
/*=====end support for handle=====*/

/*=====COMMAND HANDLERS=====*/
int handler_command_1(struct session *plr, char **cmd)
{
	if (!strcmp("me", cmd[0])) {
		plr_send_info_about(plr, plr->num);
	} else if (!strcmp("plr", cmd[0])) {
		plr_send_stat(plr);
	} else if (!strcmp("market", cmd[0])) {
		plr_send_market(plr);
	} else if (!strcmp("turn", cmd[0])) {
		/* DEBUG */ //printf("PLR[%i]: end_turn\n", plr->num);
		plr->state = fsm_end_turn;
		plr_send_string(plr, "* you end turn\n");
	} else if (!strcmp("help", cmd[0])) {
		plr_send_help(plr);
	} else {
		plr_send_string(plr, msg_warn);
		return 0;
	}
	return 1;
}

int handler_command_2(struct session *plr, char **cmd)
{
	char *endptr = NULL;
	int i, num = strtol(cmd[1], &endptr, 10);
	if (*endptr) {
		sess_send_string(plr, msg_warn);
		return 0;
	}

	if (!strcmp("plr", cmd[0])) {
		plr_send_info_about(plr, num);
	} else if (!strcmp("prod", cmd[0])) {
		if (plr->money < 2000*num) {
			plr_send_string(plr, "* not enough money\n");
		} else if (plr->material < num) {
			plr_send_string(plr, "* not enough material\n");
		} else if (plr->max_product < num) {
			plr_send_string(plr, "* not enough factories\n");
		} else {
			plr_send_string(plr, "* produced\n");
			plr->money -= 2000*num;
			plr->material -= num;
			plr->max_product -= num;
			plr_send_string(plr, "* - $");
			plr_send_int(plr, 2000*num);
			plr->product += num;
		}
	} else if (!strcmp("build", cmd[0])) {
		plr_send_string(plr, "* submited\n");
		plr->money -= 2500*num;
		plr_send_string(plr, "* - $");
		plr_send_int(plr, 2500*num);
		for (i=0;i<num;i++) {
			plr_request_build(plr);
		}
		bank_build_print();
	} else {
		sess_send_string(plr, msg_warn);
		return 0;
	}
	return 1;
}

int handler_command_3(struct session *plr, char **cmd)
{
	char *endptr1 = NULL, *endptr2 = NULL;
	int count = strtol(cmd[1], &endptr1, 10);
	int price = strtol(cmd[2], &endptr2, 10);
	if (*endptr1 || *endptr2) {
		sess_send_string(plr, msg_warn);
		return 0;
	}

	if (!strcmp("buy", cmd[0])) {
		plr_app_buy(count,price,plr);
	} else if (!strcmp("sell", cmd[0])) {
		plr_app_sell(count,price,plr);
	} else {
		sess_send_string(plr, msg_warn);
		return 0;
	}
	return 1;
}
/*=====END OF COMMAND HANDLERS=====*/

void sess_handle_command(struct session *sess, const char *line)
{
	char **cmd;
	int size;
	/* DEBUG */ //printf("PLAYER[%i]:", sess->num);
	/* DEBUG */ //printf(" handle_command: \n\t");
	/* DEBUG */ //packline_print(cmd);
	cmd = sess_handle_packline(line);
	size = packline_size(cmd);

	if (size == 1) {
		handler_command_1(sess, cmd);
	} else if (size == 2) {
		handler_command_2(sess, cmd);
	} else if (size == 3) {
		handler_command_3(sess, cmd);
	} else {
		if (*cmd)
			sess_send_string(sess, msg_warn);
	}
}

void sess_fsm_step(struct session *sess, char *line)
{
	switch(sess->state)
	{
		case fsm_wait:
			sess_send_string(sess, "* wait other plrs\n");
			break;
		case fsm_command:
			sess_handle_command(sess, line);

			bank_audit();
			bank_check_finish();
			bank_check_end_turn();

			free(line);
			break;
		/* for game: */
		case fsm_end_turn:
			sess_send_string(sess, "* wait other plrs\n");
			break;
		case fsm_finish:
			/* smt will point end of the game... */
		case fsm_close:
		case fsm_error:
			free(line);
	}
}

void sess_check_lf(struct session *sess)
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
	sess_fsm_step(sess, line);
}

int sess_read(struct session *sess)
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
	sess_check_lf(sess);
	if (sess->buf_used >= INBUFSIZE)
	{
		sess_send_string(sess, "Line too long! Goodbye...\n");
		sess->state = fsm_error;
		return 0;
	}
	if (sess->state == fsm_close)
		return 0;
	return 1;
}

void sess_cleanup(struct session *sess)
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

	printf("*market       \t%i\n",bank->m_level+1);
	printf("*m_mat   \t[%i]\t%i$\n",
		bank->m_material,
		bank->m_material_price);
	printf("*m_prod  \t[%i]\t%i$\n",
		bank->m_product,
		bank->m_product_price);

	printf("*max plrs: \t%i\n",bank->plr_max_count);
	printf("*plr_count:\t%i\n",bank->plr_count);
	for (i=4;i < 4 + bank->plr_max_count;i++) {
		if (bank->plr[i]) {
			printf("*\tplr %i [%i]\t%i$\t",i,
				bank->plr[i]->num,
				bank->plr[i]->money);
			if (bank->plr[i]->state == fsm_wait) {
				printf("waiting\n");
			} else if (bank->plr[i]->state == fsm_command) {
				printf("active\n");
			} else if (bank->plr[i]->state == fsm_end_turn) {
				printf("end turn\n");
			} else if (bank->plr[i]->state == fsm_finish) {
				printf("finish\n");
			}
		} else {
			printf("*\tplr NULL\n");
		}
	}
}

void bank_news_string(char *line)
{
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->plr[i]) {
			plr_send_string(bank->plr[i], line);
		}
	}
}

void bank_news_int(int n)
{
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->plr[i]) {
			plr_send_int(bank->plr[i], n);
		}
	}
}

void bank_news_turn()
{
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->plr[i]) {
			plr_send_string(bank->plr[i], "* MONTH ");
			plr_send_int(bank->plr[i], bank->turn);
		}
	}
}

void bank_news_finish()
{
	int i, win = -1;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->plr[i]) {
			plr_send_string(bank->plr[i], "* GAME OVER \n");
			if (bank->plr[i]->state != fsm_finish) {
				win = i;
				bank->plr[win]->state = fsm_finish;
			}
		}
	}
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->plr[i]) {
			if (win != -1) {
				plr_send_string
					(bank->plr[i], "* WINNER - PLAYER ");
				plr_send_int
					(bank->plr[i],bank->plr[win]->num);
			} else {
				plr_send_string	
					(bank->plr[i], "* WINNER - NO\n");
			}
		}
	}
}

void bank_check_count_plr()
{
	int i;
	if (bank->plr_count == bank->plr_max_count) {
		for (i=0;i < SESS_ARR_SIZE;i++) {
			if (bank->plr[i]) {
				bank->plr[i]->state = fsm_command;
			}
		}
		/* DEBUG */ printf("=====GAME START=====\n");

		bank_news_string("* GAME STARTS\n");
		bank->turn += 1;

		bank_plr_refresh_inf();

	}
}

void bank_plr_refresh_inf()
{
	struct session *plr;
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		plr = bank->plr[i];
		if (plr &&
			plr->state != fsm_finish) {
			plr->max_product = plr->factory;
			plr->app_buy = 0;
			plr->app_sell = 0;

		}
	}
}

void bank_activate_plr()
{
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if(bank->plr[i] &&
			bank->plr[i]->state != fsm_finish) {
			bank->plr[i]->state = fsm_command;
		}
	}
}

void bank_tax()
{
	struct session* plr;
	int i, total;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if(bank->plr[i] &&
			bank->plr[i]->state != fsm_finish) {
			plr = bank->plr[i];
			total = 0;
			plr->money -=  300*plr->material;
			total += 300*plr->material;
			plr->money -=  500*plr->product;
			total += 500*plr->product;
			plr->money -= 1000*plr->factory;
			total += 1000*plr->factory;
			plr_send_string(plr, "* taxes: - $");
			plr_send_int(plr, total);
		}
	}
}

void bank_check_money()
{
	/* put this in fsm_command , to tell 'you are bankrot'*/
	/* and in check_end_turn */
	/* if money < 0 -> plr->state=fsm_finish*/
	struct session* plr;
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->plr[i] &&
			bank->plr[i]->state != fsm_finish) {
			plr = bank->plr[i];
			if (plr->money < 0) {
				plr->state = fsm_finish;
				plr_send_string(plr, "* you lost\n");
			}
		}
	}
}

void bank_m_change()
{
	int i = 0, s = 0;
	int r = 1 + (int)(12.0*rand()/(RAND_MAX+1.0));
	while (s < r) {
		s += level_change[bank->m_level][i];
		i++;
	}
	/* 1 <= i <= 5*/
	i--;
	bank->m_level = i;
	/* DEBUG */ printf("BANK: m_change: %i\n", i);
}

void bank_calculate_market()
{
	int i, ml, count = 0;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if(bank->plr[i] &&
			bank->plr[i]->state != fsm_finish) {
			count += 1;
		}
	}
	ml = bank->m_level;
	bank->m_material =
		(int)(count * m_count[ml][0]);
	bank->m_material_price =
		m_price[ml][0];
	bank->m_product = 
		(int)(count * m_count[ml][1]);
	bank->m_product_price = m_price[ml][1];
}

void bank_check_end_turn()
{
	int i;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if(bank->plr[i] &&
			bank->plr[i]->state != fsm_end_turn &&
			bank->plr[i]->state != fsm_finish) {
			break;
		}
	}
	if (i == SESS_ARR_SIZE) {
		/*handle requests for auc*/
		/*handle requests for buildings*/
		/*refresh plrs inf*/
		bank->turn += 1;
		printf("=====TURN %i=====\n", bank->turn);
	
		bank_tax();
		
		bank_handle_build();
		bank_build_print();

		bank_handle_auc_buy();
		bank_handle_auc_sell();
		bank_auc_delete();
		
		bank_check_money(); /*!REPLACED*/
		bank_check_finish();
		
		bank_m_change(); /*!REPLACED*/
		bank_calculate_market();
		
		bank_plr_refresh_inf();
		
		bank_news_turn();

		bank_activate_plr();
		bank_audit();

	}
}

void bank_check_finish()
{
	int i, count=0;
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->plr[i] && bank->plr[i]->state == fsm_finish) {
			count++;
		}
	}
	if((bank->plr_count - count) == 1 || 
		(bank->plr_count - count) == 0 ||
		bank->plr_count == 1) {
		printf("=====GAME END=====\n");
		bank_news_finish();
	}
}

void bank_handle_build()
{
	int sd;
	struct session *plr;
	struct app_build *current = bank->build;
	if (current) {
		while (current) {
			sd = current->sd;
			plr = bank->plr[sd];
			if (!plr) {
				free(current);
				current = bank->build;
				continue;
			} else if (current->month == 0) {
				plr->factory += 1;
				/*delete head*/
				plr_send_string
					(plr,
					"*new factory available\n");
				bank->build = current->next;
				free(current);
				current = bank->build;
				continue;
			} else if (current->month == 1) {
				plr->money -= 2500;
				current->month -= 1;
				plr_send_string
					(plr,
					"*new factory in the next month - $");
				plr_send_int(plr, 2500);
			} else {
				current->month -= 1;
			}
			current = current->next;
		}
	}
}

void auc_buy_swap(int i, int j)
{
	int tcount, tprice, tsd;
	tcount = bank->auc_buy[i]->count;
	tprice = bank->auc_buy[i]->price;
	tsd = bank->auc_buy[i]->sd;

	bank->auc_buy[i]->count = bank->auc_buy[j]->count;
	bank->auc_buy[i]->price = bank->auc_buy[j]->price;
	bank->auc_buy[i]->sd = bank->auc_buy[j]->sd;

	bank->auc_buy[j]->count = tcount;
	bank->auc_buy[j]->price = tprice;
	bank->auc_buy[j]->sd = tsd;
}

void auc_sell_swap(int i, int j)
{
	int tcount, tprice, tsd;
	tcount = bank->auc_sell[i]->count;
	tprice = bank->auc_sell[i]->price;
	tsd = bank->auc_sell[i]->sd;

	bank->auc_sell[i]->count = bank->auc_sell[j]->count;
	bank->auc_sell[i]->price = bank->auc_sell[j]->price;
	bank->auc_sell[i]->sd = bank->auc_sell[j]->sd;

	bank->auc_sell[j]->count = tcount;
	bank->auc_sell[j]->price = tprice;
	bank->auc_sell[j]->sd = tsd;
}

void bank_handle_auc_buy()
{
	int i, j, count, price, sd;
	/*BUY*/
	struct app_auc *buy, *buy_next;
	/* SORT */
	for (j=SESS_ARR_SIZE;j>0;j--) {
		for (i=0;i<j-1;i++) {
			buy = bank->auc_buy[i];
			buy_next = bank->auc_buy[i+1];
			if (buy->price < 
				buy_next->price) {
				auc_buy_swap(i,i+1);
			}
		}
	}
	printf("SORT AUCTION BUY\n");
	bank_auc_print();

	bank_news_string("* ===AUCTION BUY===\n");
	for (i=0;i<SESS_ARR_SIZE;i++) {
		buy = bank->auc_buy[i];
		if (buy->count != 0) {
			count = buy->count;
			price = buy->price;
			sd = buy->sd;
			if (bank->m_material >= count) {
				bank->m_material -= count;
				bank->plr[sd]->money -= price*count;
				bank->plr[sd]->material += count;
				bank_news_string("* plr ");
				bank_news_int(bank->plr[sd]->num);
				bank_news_string("* \tcount:\t");
				bank_news_int(count);
				bank_news_string("* \tprice:\t- $");
				bank_news_int(price);
				bank_news_string("* \ttotal price:\t- $");
				bank_news_int(price*count);
			}
		}
	}
}

void bank_handle_auc_sell()
{
	int i, j, count, price, sd;
	/*SELL*/
	struct app_auc *sell, *sell_next;
	/* SORT */
	for (j=SESS_ARR_SIZE;j>0;j--) {
		for (i=0;i<j-1;i++) {
			sell = bank->auc_sell[i];
			sell_next = bank->auc_sell[i+1];
			if (sell->price > 
				sell_next->price) {
				auc_sell_swap(i,i+1);
			}
		}
	}
	printf("SORT AUCTION SELL\n");
	bank_auc_print();

	bank_news_string("* ===AUCTION SELL===\n");
	for (i=0;i<SESS_ARR_SIZE;i++) {
		sell = bank->auc_sell[i];
		if (sell->count != 0) {
			count = sell->count;
			price = sell->price;
			sd = sell->sd;
			if (bank->m_product >= count) {
				bank->m_product -= count;
				bank->plr[sd]->money += price*count;
				bank->plr[sd]->product -= count;
				bank_news_string("* plr ");
				bank_news_int(bank->plr[sd]->num);
				bank_news_string("* \tcount:\t");
				bank_news_int(count);
				bank_news_string("* \tprice:\t+ $");
				bank_news_int(price);
				bank_news_string("* \ttotal price:\t+ $");
				bank_news_int(price*count);
			}
		}
	}
}

void bank_auc_print()
{
	int i;
	printf("\t=====AUCTION BUY=====\n");
	for (i=0;i < SESS_ARR_SIZE /*4+bank->plr_max_count*/;i++) {
		printf("\t[count(%i)\tprice(%i)\tsd(%i)]\n",
			bank->auc_buy[i]->count,
			bank->auc_buy[i]->price,
			bank->auc_buy[i]->sd);
	}
	printf("\t=====AUCTION SELL=====\n");
	for (i=0;i < SESS_ARR_SIZE;i++) {
		printf("\t[count(%i)\tprice(%i)\tsd(%i)]\n",
			bank->auc_sell[i]->count,
			bank->auc_sell[i]->price,
			bank->auc_sell[i]->sd);
	}
}

void bank_auc_delete()
{
	int i;
	for (i=0;i<SESS_ARR_SIZE;i++)
	{
		bank->auc_buy[i]->count = 0;
		bank->auc_buy[i]->price = 0;
		bank->auc_buy[i]->sd = 0;
		bank->auc_sell[i]->count = 0;
		bank->auc_sell[i]->price = 0;
		bank->auc_sell[i]->sd = 0;
	}
}

void bank_setup(struct server_stat *serv, int max_plr)
{
	bank = malloc(sizeof(struct bank_stat));
	bank->turn = 0;
	bank->m_level = 2;
	bank->m_material = 0;
	bank->m_material_price = 0;
	bank->m_product = 0;
	bank->m_product_price = 0;

	bank->plr = serv->sess_array;
	bank->plr_max_count = max_plr;
	bank->plr_count = 0;
	
	bank->build = NULL;
	
	bank_auc_delete();
	bank_auc_print();

	bank_audit();
}
/*==========END OF BANK ACTIONS==========*/

int server_setup(struct server_stat *serv, int port, int max_plr)
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
	bank_setup(serv, max_plr);
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
		printf("warning:count of ready to connect > ARR_SIZE\n");
		return;
	}
	/* DEBUG */ printf("SERVER: accept_client: %i\n", sd);
	if (sd == -1)
	{
		perror("accept");
		return;
	}
	serv->sess_array[sd] = sess_make_new(sd, &addr);

	plr_setup(sd);
	/* BANK */
	bank_check_count_plr();
	bank_calculate_market();
	bank_audit();
}

void server_sess_close(struct server_stat *serv, int sd)
{
	/* DEBUG */ printf("SERVER: sess_close: %i\n", sd);
	close(sd);
	serv->sess_array[sd]->fd = -1;
	sess_cleanup(serv->sess_array[sd]);
	free(serv->sess_array[sd]);
	serv->sess_array[sd] = NULL;

	bank->plr_count -= 1;
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
			if (serv->sess_array[i] && FD_ISSET(i, &readfds))
			{
				printf("SERVER: call: sess_read: %i\n", i);
				ssr = sess_read(serv->sess_array[i]);
				if (!ssr)
					server_sess_close(serv, i);
			}
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	struct server_stat serv;
	//struct bank_stat bank;
	int port, max_plr;
	char *endptr;

	if (argc != 3) {
        printf("Usage: ./server <port> <num of plrs>\n");
        return 1;
    }

	port = strtol(argv[1], &endptr, 10);
	if (*endptr) {
		printf("error: wrong port\n");
		return 1;
	}

	max_plr = strtol(argv[2], &endptr, 10);
	if (*endptr || max_plr > SESS_ARR_SIZE) {
		printf("error: wrong num of plrs (max = %i)\n",
				SESS_ARR_SIZE);
		return 1;
	}
	
	/*there we alse have setup for bank*/
	if (server_setup(&serv, port, max_plr)) 
		return 1;

	server_run(&serv);
	return 0;
}
