// анализируем параметры командной строки
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int IsDaemon = 0 ;						// по умолчанию программа - не демон

void cmd_line( int argc, char *argv[] ) 			// argc - количество аргументов командной строки, argv - массив указателей на строки
{
	int k ;

	for ( k = 1 ; k < argc ; k++ )
	{
		if ( strcmp( argv[k], "--help" ) == 0 ) 	// ищем строку --help, если нашли
		{
			printf("Справка\n") ;			// печатаем справку		 
			exit(0) ;				// выходим совсем из программы
		}
	}

	for ( k = 1 ; k < argc ; k++ )
	{
		if ( strcmp( argv[k], "--daemon" ) == 0 ) 	// ищем строку --daemon, если нашли
		{
			IsDaemon = 1 ;				// устанавливаем флаг 1 
		}
	}
} 
