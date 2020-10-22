#ifndef HOMEWORK_2_PARALLEL_REALIZATION_H
#define HOMEWORK_2_PARALLEL_REALIZATION_H

typedef struct
{
    char * sequence;
    int * amount;
} for_thread;

int number_of_sequences_parallel( char ** sequences, int * amount_of_every_sequence, int count );
int finder( char * sequence );
void * my_thread( void * thread_data );

#endif //HOMEWORK_2_PARALLEL_REALIZATION_H
