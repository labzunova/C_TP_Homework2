#include "parallel_realization.h"
#include "../console_communication.h"
#include "../console_communication.c" // ??? for tests
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int finder( char * sequence, char * filename )
{
    FILE *fff;
    if ( ( fff = fopen( filename, "r" ) ) == NULL ) // TODO path
    {
        cant_open_file();
        //getchar();
        exit(-1 );
    }

    int amount = 0;
    char c = '\0';
    int matches = 0;
    while ( ( c = fgetc( fff ) ) != EOF )
    {
        if ( c == sequence[matches] ) matches++;
        else matches = 0;

        if ( matches == strlen( sequence ) )
        {
            amount++;
            matches = 0;
        }
    }
    fclose(fff);
    return amount;
}

void * my_thread( void * thread_data )
{
    for_thread * data = ( for_thread * ) thread_data;
    data->amount = ( int * ) finder( data->sequence, data->file_name );
    return NULL;
}

int number_of_sequences_parallel( char ** sequences, int * amount_of_every_sequence, const int count, char * filename )
{
    pthread_t * threads = ( pthread_t* ) malloc( count * sizeof( pthread_t ) );
    for_thread * thread_data = ( for_thread * ) malloc( count * sizeof( for_thread ) );
   for( int i = 0; i < count; i++ )
    {
        amount_of_every_sequence[i] = 0; // обнуляем счетчик каждой последовательности перед тем как запустить его в поток
        thread_data[i].amount = ( int * ) amount_of_every_sequence[i];
        thread_data[i].sequence = sequences[i];
        thread_data[i].file_name = filename;
        pthread_create( &( threads[i] ), NULL, my_thread, &thread_data[i] );
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
