// Вариант #39
// Перед вами поставлена задача поиска заданных последовательностей символов в загруженном в оперативную память файле размером 100 Мб.
// Составьте наивный алгоритм поиска, который сначала ищет вхождения первой последовательности, затем — второй и т.д.,
// а затем распараллельте его на несколько потоков с учетом оптимизации работы с кэш-памятью.

#include <malloc.h>
#include <stdio.h>
#include "console_communication.h"
#include "consistent/consistent_realization.h"
#include "parallel/parallel_realization.h"
#define CONSISTENT_METHOD 1
#define PARALLEL_METHOD 2

int main()
{
    int count = count_reading();
    char ** sequences;
    sequences = ( char ** ) malloc(count * sizeof( char * ) ) ;
    if ( !sequences ) cant_allocate();
  /*for ( int i = 0; i < count; i++ )
    {
        sequences[i] = ( char * )malloc(  sizeof( char ) * 10 ) ;
        sequences[i] = sequence_reading( i );
        printf_s( "'%s' sequence\n", sequences[0] );
        printf_s( "'%s' sequence\n", sequences[i] );
    } */
    sequences_reading( sequences, count );

   /* for ( int i = 0; i < count; i++ )
    {
        printf_s( "'%s' sequence\n", sequences[i] );
    } */

    int method = choose_method();
    int amount_of_every_sequence[count];
    if ( method == CONSISTENT_METHOD )
    {
        if ( number_of_sequences( sequences, amount_of_every_sequence, count ) == -1 ) return -1;

        for ( int i = 0; i < count; i++ )
        {
            result_output( sequences[i], amount_of_every_sequence[i] );
        }
    } else
    if ( method == PARALLEL_METHOD )
    {
        if ( number_of_sequences_parallel( sequences, amount_of_every_sequence, count ) == -1 ) return -1;
        for ( int i = 0; i < count; i++ )
        {
            result_output( sequences[i], amount_of_every_sequence[i] );
        }
    }

    /*for ( int i = 0; i < count; i++ )
        free( sequences[i] );*/
    free( sequences ); // TODO: like this?
    free( amount_of_every_sequence );
    return 0;
}
