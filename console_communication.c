#include "console_communication.h"
#include <stdio.h>
#include <stdlib.h>

int count_reading()
{
    int count = 0;
    printf( "\nEnter a number of sequences: \n" );
    while ( ( scanf( "%d", &count) != 1 )||( count <= 0 ) )  // TODO: integer check
    {
        printf( "Enter a POSITIVE INTEGER number of sequences: \n" );
        while( getchar() != '\n' ); // Чистим буфер
    };
    return count;
}

void cant_allocate()
{
    printf_s( "Error: can't allocate memory" );
    exit( 0 );
}

void cant_open_file()
{
    printf_s( "Error: can't open file" );
    exit( 0 );
}

char * sequence_reading( int i )
{
    char* sequence;
    printf_s( "       %d sequence:\n", i+1 );

    printf_s( "Enter a sequence: \n" );
    while ( ( scanf( "%s", sequence ) != 1 ) )   //TODO: integer check
    {
        printf_s(" !Enter a sequence: \n");
        while(getchar() != '\n'); // Чистим буфер
    };

    return sequence;
}