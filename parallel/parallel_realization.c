#include "parallel_realization.h"
#include "../console_communication.h"
//#include "../console_communication.c" // ??? for tests
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <sys/mman.h>
#ifdef __linux__
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif

static int finder( char * sequence, char * filename )
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

    int amount = 0;
    char c = '\0';
    int matches = 0;
    for( int j = 0; j < file_size; j++ )
    {
        c = region[j];
        if ( c == sequence[matches] )
            matches++;
        else
            matches = 0;

        if ( matches == strlen( sequence ) )
        {
            amount++;
            matches = 0;
        }
    }
    close(fff);
    if (munmap(region, file_size) != 0)
    {
        mapping_failed();
        exit( -1 );
    }
    return amount;
}

static void * my_thread( void * thread_data )
{
    for_thread * data = ( for_thread * ) thread_data;
    data->amount = ( int * ) finder( data->sequence, data->file_name );
    return NULL;
}

int number_of_sequences_parallel( char ** sequences, int * amount_of_every_sequence, const int count, char * filename )
{
    pthread_t * threads = ( pthread_t* ) malloc( count * sizeof( pthread_t ) );
    if ( !threads )
    {
        cant_allocate();
        for ( int i = 0; i < count; i++ )
            free( sequences[i] );
        free( sequences );
        exit(-1);
    }

    for_thread * thread_data = ( for_thread * ) malloc( count * sizeof( for_thread ) );
    if ( !thread_data )
    {
        cant_allocate();
        for ( int i = 0; i < count; i++ )
            free( sequences[i] );
        free( sequences );
        free( threads );
        exit(-1);
    }

    for( int i = 0; i < count; i++ )
    {
        amount_of_every_sequence[i] = 0; // обнуляем счетчик каждой последовательности перед тем как запустить его в поток
        thread_data[i].amount = ( int * ) amount_of_every_sequence[i];
        thread_data[i].sequence = sequences[i];
        thread_data[i].file_name = filename;
        if ( !pthread_create( &( threads[i] ), NULL, my_thread, &thread_data[i] ) )
        {
            cant_create_thread();
            for ( int i = 0; i < count; i++ )
                free( sequences[i] );
            free( sequences );
            free( threads );
            free( thread_data );
            exit(-1);
        }

    }

    for( int i = 0; i < count; i++ )
        pthread_join( threads[i], NULL );
    for( int i = 0; i < count; i++ )
    {
        amount_of_every_sequence[i] = ( int ) thread_data[i].amount;
    }


    free(threads);
    free(thread_data);
    return 0;
}
