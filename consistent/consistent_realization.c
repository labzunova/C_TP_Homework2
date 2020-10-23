#include "consistent_realization.h"
#include "../console_communication.h"
#include "../console_communication.c"
#include "../mman-win32/trunk/mman.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int number_of_sequences( char ** sequences, int * amount_of_every_sequence, int count, char * filename )
{
    FILE *fff;
    if ( ( fff = fopen( "D:/projects/C,C++ TechPark/Homework 2/files/homework2.txt", "r" ) ) == NULL ) // TODO path
    {
        cant_open_file();
        //getchar();
        return -1;
    }
   /* int fd = fileno( fff );
    struct stat st;
    stat( "D:/projects/C,C++ TechPark/Homework 2/files/homework2.txt", &st );
    size_t file_size = st.st_size;

    char * map = mmap( NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0 );

    if ( map ==  MAP_FAILED )
    {
        cant_open_file();
        close(fd);
        return -1;
    }*/

    for ( int i = 0; i < count; i++ )
    {
        rewind( fff );
        amount_of_every_sequence[i] = 0;
        char c = '\0';
        int matches = 0;
        //for ( int j = 0; j < file_size; j++ )
        while ( ( c = fgetc( fff ) ) != EOF )
        {
            c = ( char )fgetc( fff );
           //c = map[j];
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