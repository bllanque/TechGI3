#ifndef _STRIP_H_
#define _STRIP_H_


typedef enum
{
	OK,
	NOT_OK
} TestResult;

/* entfernt ueberfluessige Schraegstriche aus einem C-String */
char* strip(char* str);

/* testet die Implementierung von strip per Black-Box-Methode */
TestResult test_strip();



#endif //_STRIP_H_
