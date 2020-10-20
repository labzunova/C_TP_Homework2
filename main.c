// Вариант #39
// Перед вами поставлена задача поиска заданных последовательностей символов в загруженном в оперативную память файле размером 100 Мб.
// Составьте наивный алгоритм поиска, который сначала ищет вхождения первой последовательности, затем — второй и т.д.,
// а затем распараллельте его на несколько потоков с учетом оптимизации работы с кэш-памятью.

#include <stdio.h>
#include <malloc.h>
#include "console_communication.h"

int main()
{
    int count = count_reading();
    char **sequences;
    if ( !sequences = ( char** ) malloc(count * sizeof( char* ) ) ) cant_allocate();
    for ( int i = 0; i < count; i++ )
    {
        sequences[i] = sequence_reading(i);
    }
 /*
    for ( int i = 0; i < count; i++ )
    {

    }
    FILE *fff;
    if ((fff = fopen("homework1", "r")) == NULL)
    {
        cant_open_file();
        getchar();
        return 0;
    } */

    // TODO everything :)

    free( sequences );
    return 0;
}
