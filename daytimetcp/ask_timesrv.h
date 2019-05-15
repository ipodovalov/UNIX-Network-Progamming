#ifndef ASK_TIMESRV_H
#define ASK_TIMESRV_H

#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */
#include	<sys/time.h>	/* timeval{} for select() */
#include	<time.h>		/* timespec{} for pselect() */
#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include  	<signal.h>
#include    <sys/wait.h>


int die_daemon;
void catchsig( int ) ;
int serveraction( int connfd );
int make_socket(int*, int*);

#endif // ASK_TIMESRV_H


