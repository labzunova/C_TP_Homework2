#include "console_communication.h"
#include <stdio.h>
#include <stdlib.h>
#define CONSISTENT_METHOD 1
#define PARALLEL_METHOD 2

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
    printf_s( "\n! ERROR: can't allocate memory" );
    exit( -1 );
}

void cant_open_file()
{
    printf_s( "\n! ERROR: can't open file" );
    exit( -1 );
}

int choose_method()
{
    int method = 0;
    printf( "\nWhich method do you want to use?:\n1 - consistent\n2 - parallel\n" );
    while ( ( scanf( "%d", &method) != 1 )||( ( method != CONSISTENT_METHOD ) && ( method != PARALLEL_METHOD ) ) )
    {
        printf( "Enter 1 or 2: \n" );
        while( getchar() != '\n' ); // Чистим буфер
    };
    printf( "\n" );
    if ( method == CONSISTENT_METHOD ) return CONSISTENT_METHOD;
    else return PARALLEL_METHOD;
}

void sequences_reading( char ** sequences, int count )
{
    for ( int i = 0; i < count; i++ )
    {
        sequences[i] = ( char * )malloc( sizeof( char ) * 10 ); // TODO: come up smth with this magic number
        if ( !sequences[i] ) cant_allocate();
        printf_s( " %d sequence:\n", i+1 );
        printf_s( "Enter a sequence: \n" );
        while ( scanf( "%s", sequences[i] ) != 1 )
        {
            printf_s(" !Enter a sequence: \n");
            while( getchar() != '\n' );
        };
    }
}

void result_output(char * sequence, int amount)
{
    printf_s( "'%s' sequence amount in file is %d:\n", sequence, amount );
}