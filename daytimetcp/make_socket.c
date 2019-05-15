#include "ask_timesrv.h"
#define	LISTENQ		1024	/* 2nd argument to listen() */
#define	MAXLINE		4096	/* max text line length */
#define	MAXSOCKADDR  128	/* max socket address structure size */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

//int			        listenfd, connfd;
extern struct sockaddr_in  servaddr;			     // структура адреса сокета IPv4
extern struct sockaddr_in  clientaddr;               // сюда accept() помещает адрес подключившегося клиента
extern socklen_t 		   addrclientlen ;		     // тоже для accept()

int make_socket(int* listenfd, int* connfd){
                        // TODO запрятать сокетные дела в отдельную функцию
    int lstn;
	lstn = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));		// заполнить структуру нулями перед использованием
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(13);	// стандартный порт сервера времени

                                        /*
                функция bind связывает сокет listenfd с локальным адресом сервера
                (в нашем случае это любой (INADDR_ANY) активный сетевой интерфейс на сервере.
                Запросто можно было присвоить адрес конктретного интерфейса переменной
                servaddr.sin_addr.s_addr (используя функцию преобразования адресов, напр:
                inet_pton(AF_INET, "192.168.0.42", &servaddr.sin_addr.s_addr);
                и тогда соединение будет приниматься только на него
                                        */
	bind(lstn, (struct sockaddr *) &servaddr, sizeof(servaddr));

                                        /*
                вызов функции listen характерен только для сервера и 
                необходим для того, чтобы преобразовать сокет listenfd
                в пассивный сокет, запросы на подключение к которому начинают
                приниматься ядром, второй параметр задаёт максимальное число
                соединений 
                                        */
	listen(lstn, LISTENQ);
    *listenfd=lstn;
    return 0;
}
