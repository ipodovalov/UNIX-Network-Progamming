 #include "ask_timesrv.h"
#define	MAXLINE		4096	/* max text line length */

int serveraction(int connfd)
{
    u_int8_t        timebuff[4];        // в этот массив будем помещать секунды от начала эпохи 
    char            timestrbuff[26];    // в этот массив будем помещать строку со временем и датой
	char			buff[MAXLINE];      // этот массив будем отправлять
	time_t			ticks;
    
    // сервер может заниматься обработкой данных клиента долго, поэтому у нас параллельный сервер
    // sleep(20);                       // чтобы обслуживать других клиентов
    
    // узнаём время сервера
	ticks = time(NULL);

    // получим строку со временем и датой
	snprintf(timestrbuff, sizeof(timestrbuff), "%.24s\r\n", ctime(&ticks));

    // поместим секунды от начала эпохи в массив
    u_int32_t t = ticks;
    timebuff[3] = t >> 24;
    timebuff[2] = t >> 16;
    timebuff[1] = t >> 8;
    timebuff[0] = (u_int8_t) t;
    
    // соединиям два массива перед отправкой (с принимающей стороной договариваемся о протоколе)
    // то есть в 1-х отправленных четырёх байтах секунды от начала эпохи, остальное - строка с датой-временем
    strcat(buff, timebuff);
    strcat(buff, timestrbuff);
    
    // записываем массив в сокет
	if (write(connfd, buff, strlen(buff))>0)
		return 0;
	else
		return -1;
}

