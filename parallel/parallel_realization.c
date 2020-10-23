#include "parallel_realization.h"
#include "../console_communication.h"
#include "../console_communication.c" // ??? for tests
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

int finder( char * sequence )
{
    FILE *fff;
    if ( ( fff = fopen( "D:/projects/C,C++ TechPark/Homework 2/files/homework2.txt", "r" ) ) == NULL ) // TODO path
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
           // printf_s( "'%s' amount %d\n", sequence, amount );
            matches = 0;
        }
    }
  //  printf_s( "'%s' amount %d\n", sequence, amount );
    fclose(fff);
    return amount;
}

void * my_thread( void * thread_data )
{
    for_thread * data = ( for_thread * ) thread_data;
    data->amount = ( int * ) finder( data->sequence );

    //printf_s( "'%s' amount %d\n", data->sequence, data->amount );
    //sleep(1);
    return NULL;
}

int number_of_sequences_parallel( char ** sequences, int * amount_of_every_sequence, const int count)
{
    pthread_t* threads = ( pthread_t* ) malloc( count * sizeof( pthread_t ) );
    for_thread * thread_data = ( for_thread * ) malloc( count * sizeof( for_thread ) );
    for( int i = 0; i < count; i++ )
    {
        amount_of_every_sequence[i] = 0; // обнуляем счетчик каждой последовательности перед тем как запустить его в поток
        thread_data[i].amount = ( int * ) amount_of_every_sequence[i];
        thread_data[i].sequence = sequences[i];
     //   printf_s( "'%s' amount %d\n", thread_data[i].sequence, thread_data[i].amount );
        pthread_create( &( threads[i] ), NULL, my_thread, &thread_data[i] );
    }

   /* for( int i = 0; i < count; i++ )
    {
        printf_s( "'%s' amount %d\n", thread_data[i].sequence, thread_data[i].amount );
    } */

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
