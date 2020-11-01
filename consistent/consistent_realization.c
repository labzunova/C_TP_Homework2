#include "consistent_realization.h"
#include "../console_communication.h"
//#include "../console_communication.c"
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef __linux__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

int number_of_sequences( char ** sequences, int * amount_of_every_sequence, int count, char * filename )
{
    int fff = open( filename, O_RDONLY );
    struct stat st;
    stat(filename, &st);
    size_t file_size = st.st_size;
    char *region = mmap( NULL, file_size, PROT_READ,  PROT_READ | PROT_WRITE, fff, 0 );
    if ( region == MAP_FAILED )
    {
        mapping_failed();
        exit( -1 );
    }

    for ( int i = 0; i < count; i++ )
    {
        amount_of_every_sequence[i] = 0;
        char c = '\0';
        int matches = 0;
        char * current_sequence = sequences[i];
        for( int j = 0; j < file_size; j++ )
        {
            c = region[j];
            if ( c == current_sequence[matches] ) matches++;
            else matches = 0;

            if ( matches == strlen( current_sequence ) )
            {
                amount_of_every_sequence[i]++;
                matches = 0;
            }
        }
    }
    close(fff);
    if (munmap(region, file_size) != 0)
    {
        mapping_failed();
        exit( -1 );
    }
    return 0;
}