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
#define SESS_ARR_SIZE 32

int global_count = 0;

enum fsm_states {
	fsm_start,
	fsm_command = fsm_start,
	fsm_finish,
	fsm_error
};

struct session {
	int fd;
	unsigned long from_ip;
	unsigned short from_port;
	char buf[INBUFSIZE];
	int buf_used;
	enum fsm_states state;
	/*for game: there must be information about resources*/
};

/*procedure*/
/*for game: send to all players news (what have just changed)*/

/*==========SESSION ACTIONS==========*/
void session_send_string(struct session *sess, const char *str)
{
	write(sess->fd, str, strlen(str));
}

void session_send_int(struct session *sess, const int n)
{
	char send[256];
	sprintf(send, "%i", global_count);
	session_send_string(sess, send);
	session_send_string(sess, "\n");
}

struct session *session_make_new(int fd, struct sockaddr_in *from)
{
	struct session *sess = malloc(sizeof(*sess));
	sess->fd = fd;
	sess->from_ip = ntohl(from->sin_addr.s_addr);
	sess->from_port = ntohs(from->sin_port);
	sess->buf_used = 0;
	sess->state = fsm_start;
	/*for game: setup information about resources*/
	session_send_string(sess, "Type 'increment' or 'decrement'\n");
	return sess;
}

void session_handle_command(struct session *sess, const char *line)
{
	/* DEBUG */ printf("handle_command: [%s]\n", line);
	/* DEBUG */ printf
		("handle_command: old global_count = %i\n", global_count);
	if (!strcmp("increment", line)) {
		global_count++;
		session_send_int(sess, global_count);
	} else if (!strcmp("decrement", line)) {
		global_count--;
		session_send_int(sess, global_count);
	} else {
		session_send_string(sess, "Wrong command!\n");
		session_send_string(sess, "Type 'increment' or 'decrement'\n");
	}
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

	if (line[pos-1] == '\r') /* what is it? */
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
	struct session **sess_array;
	int sess_array_size;
};

int server_setup(struct server_stat *serv, int port)
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
	return 0;
}

void server_accept_client(struct server_stat *serv)
{
	int sd;
	struct sockaddr_in addr;
	socklen_t len = sizeof(addr);
	sd = accept(serv->ls, (struct sockaddr*) &addr, &len);
	/* DEBUG */ printf("new connection %i\n", sd);
	if (sd == -1)
	{
		perror("accept");
		return;
	}
	serv->sess_array[sd] = session_make_new(sd, &addr);
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
	int port;
	char *endptr;

	if (argc != 2) {
        printf("Usage: ./server <port>\n");
        return 1;
    }

	port = strtol(argv[1], &endptr, 10);
	if (*endptr) {
		printf("error: wrong port\n");
		return 1;
	}

	if (server_setup(&serv, port))
		return 1;

	server_run(&serv);
	return 0;
}
