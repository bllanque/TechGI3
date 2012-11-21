/* *********************************************** *
 * Diese Vorgabedatei soll NICHT geändert werden.  *
 *                                                 *
 * Verzichten sie auch dann auf Änderungen, wenn   *
 * dadurch ihr Programm einfacher oder eleganter   *
 * wird!                                           *
 * *********************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vorgabe.h"

int main( int argc, char** argv ) {

	if ( argc > 1 )
		if ( argv[1][0] == 'r' ) srand(( unsigned )time( NULL ) );
	init_sim();

	test( "FIFO", 0 );
	if ( implemented[0] )get_statistics( "FIFO", 0 );
	printf( "\n" );

	test( "SJN", 1 );
	if ( implemented[1] )get_statistics( "SJN", 1 );
	printf( "\n" );

	test( "RR_1", 2 );
	if ( implemented[2] )get_statistics( "RR_1", 2 );
	printf( "\n" );

	test( "RR_3", 3 );
	if ( implemented[3] )get_statistics( "RR_3", 3 );
	printf( "\n" );

	test( "RR_MLF", 4 );
	if ( implemented[4] )get_statistics( "RR_MLF", 4 );

	return 0;
}
