#include "ask_timesrv.h"

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	MAXSOCKADDR  128	/* max socket address structure size */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */
#define	LISTENQ		1024	/* 2nd argument to listen() */

int			listenfd, connfd;
struct sockaddr_in	servaddr;			// структура адреса сокета IPv4
struct sockaddr_in      clientaddr;     // сюда accept() помещает адрес подключившегося клиента
socklen_t 		addrclientlen ;			// тоже для accept()

int
ask_timesrv()
{
	struct sigaction sa ;				// структура для управления сигналами
	sigemptyset(&sa.sa_mask) ;			// очищаем маску сигналов (не текущего процесса, а структуры sa)
	sa.sa_handler = catchsig ;			// указатель на функцию-обработчик сигналов
	sa.sa_flags = 0|SA_NODEFER ;	
	sigaction(SIGTERM, &sa, NULL) ;		// для корректного завершения
	sigaction(SIGUSR1, &sa, NULL) ;		// устанавливает новую диспозицию для сигнала SIGUSR1
	sigaction(SIGUSR2, &sa, NULL) ;
	sigaction(SIGINT, &sa, NULL) ;
    sigaction(SIGCHLD, &sa, NULL);         // также подменим обработчик сигнала SIGCHLD для завершения дочерних процессов-зомби
    
	char			buff[MAXLINE], buff_addr[MAXLINE];
	time_t			ticks;
    
    pid_t pid;
    make_socket(&listenfd, &connfd);    
    
	die_daemon = 1;
	while (die_daemon) {
		
	connfd = accept(listenfd, (struct sockaddr *) &clientaddr, &addrclientlen);
 //printf("kjhg;hrh;");
        
	if (connfd>0){
          if ((pid=fork())==0){
               close(listenfd);
               
               // вызов функции, выполняющей основное действие сервера
               // TODO проанализировать возвращаемое значение
               serveraction(connfd);
               close(connfd); 
               exit(0);
               
          }
           else {
            ticks = time(NULL);
            snprintf(buff, sizeof(buff), "%.24s", ctime(&ticks));
            // Лог-запись сервера о подключившемся клиенте
			printf("\n%s : Запрос от %s:%d\n", buff, inet_ntop(AF_INET, &clientaddr.sin_addr, buff_addr, sizeof(buff_addr)),             ntohs(clientaddr.sin_port));
           }
		}
    }

	close(connfd); // закрываем сокет только при получении сигнала (выходе из программы)
}

void catchsig(int sig)
{
	switch (sig) 
	{
		case SIGUSR1: printf("\nПолучен сигнал SIGUSR1\n") ; break ;
		case SIGUSR2: printf("\nПолучен сигнал SIGUSR2\n") ; break ;
        case SIGCHLD: printf("\nПолучен сигнал SIGCHLD\n"); wait(NULL); break;
		case SIGTERM: printf("\nПолучен сигнал SIGTERM\n") ; die_daemon = 0 ; break ;
		case SIGINT: printf("\nПолучен сигнал SIGINT\n") ; die_daemon = 0 ; break ;
	}
}


