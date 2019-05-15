#include "ask_timesrv.h"

void cmd_line ( int argc, char *argv[] ) ;
int ask_timesrv();
extern int IsDaemon;

int main( int argc, char * argv[] )
{
	pid_t iChild ;					// для хранения идентификатора процесса

	cmd_line( argc, argv ) ;		// проверяем и обрабатываем параметры командной строки

	if ( IsDaemon )					// если ключ --daemon использовался (запускаем как демон)
	{
		printf( "Стартуем..." ) ;

		iChild = fork() ;			// теперь выполняется два процесса
		if ( iChild < 0 )
		{
			printf( "Ошибка запуска сервера: %d.", errno ) ;
			return 1 ;
		}

		if ( iChild )	 			// родительский процесс завершаем, дочерний процесс будет демоном
		{
			printf( "Cервер запущен в режиме демона" ) ;
			return 0 ;
		}
	}

	return ask_timesrv( ) ;
}
