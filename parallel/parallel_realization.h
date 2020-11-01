#ifndef HOMEWORK_2_PARALLEL_REALIZATION_H
#define HOMEWORK_2_PARALLEL_REALIZATION_H

typedef struct
{
    char * sequence;
    int * amount;
    char * file_name;
} for_thread;

int number_of_sequences_parallel( char ** sequences, int * amount_of_every_sequence, int count, char * filename );

#endif //HOMEWORK_2_PARALLEL_REALIZATION_H
