#include "consistent_realization.h"
#include "../console_communication.h"
//#include "../console_communication.c"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int number_of_sequences( char ** sequences, int * amount_of_every_sequence, int count, char * filename )
{
    FILE *fff;
    if ( ( fff = fopen( filename, "r" ) ) == NULL ) // TODO path
    {
        cant_open_file();
        exit(-1);
    }

    for ( int i = 0; i < count; i++ )
    {
        rewind( fff );
        amount_of_every_sequence[i] = 0;
        char c = '\0';
        int matches = 0;
        char * current_sequence = sequences[i];
        while ( ( c = fgetc( fff ) ) != EOF )
        {
            if ( c == current_sequence[matches] ) matches++;
            else matches = 0;

            if ( matches == strlen( current_sequence ) )
            {
                amount_of_every_sequence[i]++;
                matches = 0;
            }
        }
    }
    fclose(fff);
    return 0;
}