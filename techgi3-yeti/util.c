#include "util.h"

#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

unsigned long current_time_millis()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec*1000L + time.tv_usec/1000L);
}


void search_and_insert(char* chunk, unsigned int size, ringbuffer_t* buf)
{
	char result[RESULTSIZE];
	unsigned int resultlen = 0;
	char* found;
	unsigned int start;
	/*fuer jeden moeglichen String*/
	for(start = 0; start < size; ++start)
	{
		unsigned  int offs;
		/* fuer jeden moeglichen vergleichbaren String */
		for(offs = MINLEN; (offs < RESULTSIZE) && (start + offs < size); ++offs)
		{
			/* Gemeinsamkeiten Suchen */
			resultlen = 0;
			while(chunk[start + resultlen] == chunk[start + offs + resultlen])
			{
				result[resultlen] = chunk[start + resultlen];
				resultlen++;
			}
			/* mehr als 10 gemeinsame Zeichen? */
			if(resultlen >= 10)
			{
				/* Ergebnis in Puffer einfuegen */
				found = (char*) malloc((RESULTSIZE) * sizeof(char));
				memcpy(found, result, resultlen);
				found[resultlen] = '\0';
				deposit(buf, found);
				/* hinter Wiederholung weitersuchen*/
				start += resultlen;
				break;
			}
		}
	}
}

