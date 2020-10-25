#include "consistent_realization.h"
#include "../console_communication.h"
#include "../console_communication.c"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int number_of_sequences( char ** sequences, int * amount_of_every_sequence, int count, char * filename )
{
    FILE *fff;
    if ( ( fff = fopen( filename, "r" ) ) == NULL ) // TODO path
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