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

#define INBUFSIZE 128
#define SESS_ARR_SIZE 16

int global_count = 0;

enum fsm_states {
	fsm_start,
	fsm_command = fsm_start,
	fsm_finish,
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
	// ? int status;
	int number; /*number of player*/ /*depends on count of players*/
	int money; /* 10000 */ /*start count*/
	int material; /* 4 */
	int product; /* 2 */
	int factory; /* 2 */
};

struct bank_stat {
	struct session **player; /*equals sess_array in serv, it's same*/
	int player_max_count; /*we wait for N players before the start*/
	int player_count;
};

struct bank_stat *bank;

void bank_audit();

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
}

void player_send_info(int sd)
{
	struct session *player;
	player = bank->player[sd];
	player_send_string(player,"* Number:     \t");
	player_send_int(player, player->number);
	player_send_string(player,"* Money:      \t");
	player_send_int(player, player->money);
	player_send_string(player,"* Material:   \t");
	player_send_int(player, player->material);
	player_send_string(player,"* Product:    \t");
	player_send_int(player, player->product);
	player_send_string(player,"* Factory:    \t");
	player_send_int(player, player->factory);
}

struct session *session_make_new(int fd, struct sockaddr_in *from)
{
	struct session *sess = malloc(sizeof(*sess));
	sess->fd = fd;
	sess->from_ip = ntohl(from->sin_addr.s_addr);
	sess->from_port = ntohs(from->sin_port);
	sess->buf_used = 0;
	sess->state = fsm_start;

	session_send_string(sess, "* Welcome to the game server\n");
	session_send_string(sess, "* Type 'myinfo' for your statistic\n");
	/*for game: setup information about resources*/
		/*SOLVED in accept_client*/
	return sess;
}

/*=====support for handle=====*/
int word_count(char *line)
{
	int size = 0;
	char *temp = NULL, *word, *sep = " ";
	strcpy(temp, line);
	for(word=strtok(temp,sep);
		word;
		word=strtok(NULL,sep))
		size++;
	return size;
}

void packline_print(char **packline)
{
	char **temp = packline;
	while(temp[0]) {
		printf("[%s]\n", temp[0]);
		temp++;
	}
}
/*=====end support for handle=====*/

char **session_handle_packline(const char *line)
{
	char **packline;
	char *temp = NULL, *word, *sep = " ";
	int i, size;
	strcpy(temp, line);
	size = word_count(temp);
	packline = malloc((size+1)*sizeof(char*));
	packline[size] = NULL;
	temp = line;
	for (i=0;i<size;i++)
	{
		word = strtok(temp, sep);
		packline[i] = word;
	}
	/* DEBUG */ packline_print(packline);
	return packline;
}

void session_handle_command(struct session *sess, const char *line)
{
	char **packline;
	/* DEBUG */ printf("PLAYER %i\n", sess->number);
	/* DEBUG */ printf("handle_command: [%s]\n", line);
	packline = session_handle_packline(line);
	/*
	if (!strcmp("myinfo", line)) {
		player_send_info(sess->fd);
	} else {
		session_send_string(sess, "* Wrong command!\n");
		session_send_string(sess, "* Type 'help' for commands\n");
	}
	*/
	/* smt for change resources*/
}

void session_fsm_step(struct session *sess, char *line)
{
	switch(sess->state)
	{
		case fsm_command:
			session_handle_command(sess, line);
			free(line);
			break;
		/* for game:
		case: fsm_end_turn? 
			...
		*/ 
		/* somewhere must be procedure for check 'are all users end?'
		void server_end_turn(clients fds) */
		case fsm_finish:
			/* smt will point end of the game... */
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

	/*DEBUG*/ //printf("check_lf: [%s]\n", line);
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
		sess->state = fsm_finish;
	}
	sess->buf_used += rr;
	session_check_lf(sess);
	if (sess->buf_used >= INBUFSIZE)
	{
		session_send_string(sess, "Line too long! Goodbye...\n");
		sess->state = fsm_error;
		return 0;
	}
	if (sess->state == fsm_finish)
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

void bank_audit()
{
	int i;
	printf("***BANK AUDIT***\n");
	printf("max players:\t%i\n",bank->player_max_count);
	printf("player_count:\t%i\n",bank->player_count);
	for (i=0;i < SESS_ARR_SIZE;i++) {
		if (bank->player[i])
			printf("\tplayer %i [%i]\n",i,bank->player[i]->number);
		else
			printf("\tplayer NULL\n");
	}
	printf("\n");
}

void bank_setup(struct server_stat *serv, int max_player)
{
	bank = malloc(sizeof(bank));
	bank->player = serv->sess_array;
	bank->player_max_count = max_player;
	bank->player_count = 0;
	bank_audit();
}

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
		printf("warning: count of ready to connect > SESS_ARR_SIZE");
		return;
	}
	/* DEBUG */ printf("new connection %i\n", sd);
	if (sd == -1)
	{
		perror("accept");
		return;
	}
	serv->sess_array[sd] = session_make_new(sd, &addr);
	player_setup(sd);
	bank_audit();
}

void server_session_close(struct server_stat *serv, int sd)
{
	/* DEBUG */ printf("close connection %i\n", sd);
	close(sd);
	serv->sess_array[sd]->fd = -1;
	session_cleanup(serv->sess_array[sd]);
	free(serv->sess_array[sd]);
	serv->sess_array[sd] = NULL;
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
				printf("try to read from sess %i\n", i);
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
		printf("error: wrong number of players (max = 32)\n");
		return 1;
	}
	
	/*there we alse have setup for bank*/
	if (server_setup(&serv, port, max_player)) 
		return 1;
	

	server_run(&serv);
	return 0;
}
