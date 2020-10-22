#include "consistent_realization.h"
#include "../console_communication.h"
#include <stdio.h>
#include <string.h>

int number_of_sequences( char ** sequences, int * amount_of_every_sequence, int count )
{
    FILE *fff;
    if ( ( fff = fopen( "D:/projects/C,C++ TechPark/Homework 2/files/homework2.txt", "r" ) ) == NULL ) // TODO path
    {
        cant_open_file();
        //getchar();
        return -1;
    }

    for ( int i = 0; i < count; i++ )
    {
        rewind( fff );
        amount_of_every_sequence[i] = 0;
        char c = '\0';
        int matches = 0;
        while ( ( c = fgetc( fff ) ) != EOF )
        {
            if ( c == sequences[i][matches] ) matches++;
            else matches = 0;

            if ( matches == strlen( sequences[i] ) )
            {
                amount_of_every_sequence[i]++;
                matches = 0;
            }
        }
    }
    fclose(fff);
    return 0;
}