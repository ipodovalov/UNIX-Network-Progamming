#include	"unp.h"

int
main(int argc, char **argv)
{
	union {
	    short  s;
            char   c[sizeof(short)];
    	} un; // объявленная переменная un занимает в памяти только 2 байта
	// для объединенияя компилятор выделяет столько памяти, чтобы в ней
	// поместился самый большой член

	un.s = 0x0102; // помещаем двух-байтовое значение в самый большой член объединения
	// после этого однобайтовый член объединения c[0] и c[1] будут содержать значения
	// в зависимости от порядка байтов в системе.

	if (sizeof(short) == 2) {
		if (un.c[0] == 1 && un.c[1] == 2)
			printf("big-endian\n");
		else if (un.c[0] == 2 && un.c[1] == 1)
			printf("little-endian\n");
		else
			printf("unknown\n");
	} else
		printf("sizeof(short) = %d\n", sizeof(short));

	exit(0);
}
