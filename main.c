// Вариант #39
// Перед вами поставлена задача поиска заданных последовательностей символов в загруженном в оперативную память файле размером 100 Мб.
// Составьте наивный алгоритм поиска, который сначала ищет вхождения первой последовательности, затем — второй и т.д.,
// а затем распараллельте его на несколько потоков с учетом оптимизации работы с кэш-памятью.

#include <malloc.h>
#include <stdlib.h>
#include <sys/mman.h>
//#include "console_communication.h"
#include "consistent/consistent_realization.h"
#include "parallel/parallel_realization.h"
#define CONSISTENT_METHOD 1
#define PARALLEL_METHOD 2

int main()
{
    int count = count_reading();
    char ** sequences;
    sequences = ( char ** ) malloc(count * sizeof( char * ) ) ;
    if ( !sequences )
    {
        cant_allocate();
        exit(-1);
    }
    sequences_reading( sequences, count );

    int method = choose_method();
    int amount_of_every_sequence[count];
    if ( method == CONSISTENT_METHOD )
    {
        if ( number_of_sequences( sequences, amount_of_every_sequence, count, "../files/test1.txt") == -1 ) return -1;

        for ( int i = 0; i < count; i++ )
        {
            result_output( sequences[i], amount_of_every_sequence[i] );
        }
    } else
    if ( method == PARALLEL_METHOD )
    {
        if ( number_of_sequences_parallel( sequences, amount_of_every_sequence, count, "../files/test1.txt" ) == -1 ) return -1;
        for ( int i = 0; i < count; i++ )
        {
            result_output( sequences[i], amount_of_every_sequence[i] );
        }
    }

    for ( int i = 0; i < count; i++ )
        free( sequences[i] );
    free( sequences );
    return 0;
}
