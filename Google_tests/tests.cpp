#include <fibersapi.h>
#include "gtest/gtest.h"
#include <stdio.h>
#include <windows.h>
extern "C" {
#include "../parallel/parallel_realization.h"
#include "../consistent/consistent_realization.h"
}
#include <iostream>
#include <chrono>
#define TESTFILE_1 "D:/projects/C,C++ TechPark/Homework 2/files/test1.txt"
#define TESTFILE_2 "D:/projects/C,C++ TechPark/Homework 2/files/100mb.txt"
#define TESTFILE_3 "stress_test"
#define TESTFILE_4 "D:/projects/C,C++ TechPark/Homework 2/files/test2.txt"
#define SIZE 3
#define MINASCII 97
#define MAXASCII 122
using namespace std::chrono;


TEST( comparison, 3_sequences )
{
    // определяем тип "указатель на функцию"
    typedef void __cdecl (*dll_func)( char ** sequences, int * amount_of_every_sequence, int count, char * filename );

    dll_func number_of_sequences_parallel = NULL;
    HMODULE hDLL = LoadLibrary("../libparallel.dll");
    if (!hDLL) FAIL();

    // пытаемся найти в таблице экспортDа необходимую нам функцию
    number_of_sequences_parallel = (dll_func)GetProcAddress(hDLL, "number_of_sequences_parallel");
    if (!number_of_sequences_parallel) FAIL();

    char ** sequences = ( char ** )malloc( SIZE * sizeof( char * ) );

    for( int i = 0; i < SIZE; i++ )
        sequences[i] = ( char * )malloc( sizeof( char ) * SIZE );

    strcpy( sequences[0], ( "aa" ) );
    strcpy( sequences[1], ( "bb" ) );
    strcpy( sequences[2], ( "zz" ) );

    int amount_of_every_sequence_consistent[SIZE];
    int amount_of_every_sequence_parallel[SIZE];

    number_of_sequences( sequences, amount_of_every_sequence_consistent, SIZE, (char * ) TESTFILE_1 );
    number_of_sequences_parallel( sequences, amount_of_every_sequence_parallel, SIZE, (char * ) TESTFILE_1 );

    for ( int i = 0; i < SIZE; i++ )
    {
        ASSERT_EQ( amount_of_every_sequence_consistent[i], amount_of_every_sequence_parallel[i] );
        free( sequences[i] );
    }
    free( sequences );

    FreeLibrary(hDLL); // Выгрузка динамической библиотеки из памяти
}

TEST( comparison, file_100mb )
{
    typedef void __cdecl (*dll_func)( char ** sequences, int * amount_of_every_sequence, int count, char * filename );
    dll_func number_of_sequences_parallel = NULL;
    HMODULE hDLL = LoadLibrary("../libparallel.dll");
    if (!hDLL) FAIL();
    number_of_sequences_parallel = (dll_func)GetProcAddress(hDLL, "number_of_sequences_parallel");
    if (!number_of_sequences_parallel) FAIL();

    char ** sequences = ( char ** )malloc( SIZE * sizeof( char * ) );

    for( int i = 0; i < SIZE; i++ )
        sequences[i] = ( char * )malloc( sizeof( char ) * SIZE );

    strcpy( sequences[0], ( "Gatsby" ) );
    strcpy( sequences[1], ( "aa" ) );
    strcpy( sequences[2], ( "zz" ) );

    int amount_of_every_sequence_consistent[SIZE];
    int amount_of_every_sequence_parallel[SIZE];

    system_clock::time_point start = system_clock::now();
    number_of_sequences( sequences, amount_of_every_sequence_consistent, SIZE, (char * ) TESTFILE_2 );
    system_clock::time_point end = system_clock::now();
    duration<double> consistent = end - start;
    std::cout << "consistent: " << consistent.count() << " sec";

    start = system_clock::now();
    number_of_sequences_parallel( sequences, amount_of_every_sequence_parallel, SIZE, (char * ) TESTFILE_2 );
    end = system_clock::now();
    duration<double> parallel = end - start;
    std::cout << "\nparallel: " << parallel.count() << " sec";

    for ( int i = 0; i < SIZE; i++ )
    {
        ASSERT_EQ( amount_of_every_sequence_consistent[i], amount_of_every_sequence_parallel[i] );
        free( sequences[i] );
    }
    free( sequences );
    FreeLibrary(hDLL); // Выгрузка динамической библиотеки из памяти
}

TEST( comparison, stress )
{
    typedef void __cdecl (*dll_func)( char ** sequences, int * amount_of_every_sequence, int count, char * filename );
    dll_func number_of_sequences_parallel = NULL;
    HMODULE hDLL = LoadLibrary("../libparallel.dll");
    if (!hDLL) FAIL();
    number_of_sequences_parallel = (dll_func)GetProcAddress(hDLL, "number_of_sequences_parallel");
    if (!number_of_sequences_parallel) FAIL();

    FILE *fff;
    if ( ( fff = fopen( "stress_test", "w" ) ) == NULL ) // TODO path
        FAIL();

    srand(time( NULL ) );
    for( int i = 0; i < 100; i++ ) // запись в файл ста случайных строк случайной длины
    {
        int N = rand();
        char * string = ( char * ) malloc ( N * sizeof( char * ) );
        for ( int j = 0; j < N; j++ )
        {
            string[j] = char( rand() % ( MAXASCII - MINASCII + 1 ) +  MINASCII );
        }
        fputs( string , fff );
        free( string );
    }

    char ** sequences = ( char ** )malloc( SIZE * sizeof( char * ) );

    for( int i = 0; i < SIZE; i++ )
        sequences[i] = ( char * )malloc( sizeof( char ) * SIZE );

    // генерируем три случайных символов для поиска
    sequences[0][1] = ( char ) ( rand() % ( MAXASCII - MINASCII + 1 ) +  MINASCII );
    sequences[1][1] = ( char ) ( rand() % ( MAXASCII - MINASCII + 1 ) +  MINASCII );
    sequences[2][1] = ( char ) ( rand() % ( MAXASCII - MINASCII + 1 ) +  MINASCII );

    int amount_of_every_sequence_consistent[SIZE];
    int amount_of_every_sequence_parallel[SIZE];
    number_of_sequences( sequences, amount_of_every_sequence_consistent, SIZE, ( char *) TESTFILE_3 );
    number_of_sequences_parallel( sequences, amount_of_every_sequence_parallel, SIZE, (char * ) TESTFILE_3 );

    for ( int i = 0; i < SIZE; i++ )
    {
        ASSERT_EQ( amount_of_every_sequence_consistent[i], amount_of_every_sequence_parallel[i] );
        free( sequences[i] );
    }
    free( sequences );
    FreeLibrary(hDLL);
}

TEST( consistent, 1st )
{
    char ** sequences = ( char ** )malloc( SIZE * sizeof( char * ) );

    for( int i = 0; i < SIZE; i++ )
        sequences[i] = ( char * )malloc( sizeof( char ) * SIZE );

    strcpy( sequences[0], ( "aa" ) );
    strcpy( sequences[1], ( "bb" ) );
    strcpy( sequences[2], ( "zz" ) );

    int amount_of_every_sequence_consistent[SIZE];

    number_of_sequences( sequences, amount_of_every_sequence_consistent, SIZE, (char * ) TESTFILE_1 );

    ASSERT_EQ( amount_of_every_sequence_consistent[0], 3 );
    ASSERT_EQ( amount_of_every_sequence_consistent[1], 0 );
    ASSERT_EQ( amount_of_every_sequence_consistent[2], 0 );
    for ( int i = 0; i < SIZE; i++ ) free( sequences[i] );
    free( sequences );
}

TEST( consistent, 2nd )
{
    char ** sequences = ( char ** )malloc( SIZE * sizeof( char * ) );

    for( int i = 0; i < SIZE; i++ )
        sequences[i] = ( char * )malloc( sizeof( char ) * SIZE );

    strcpy( sequences[0], ( "Hello" ) );
    strcpy( sequences[1], ( "world" ) );
    strcpy( sequences[2], ( "!" ) );

    int amount_of_every_sequence_consistent[SIZE];

    number_of_sequences( sequences, amount_of_every_sequence_consistent, SIZE, (char * ) TESTFILE_4 );

    ASSERT_EQ( amount_of_every_sequence_consistent[0], 9 );
    ASSERT_EQ( amount_of_every_sequence_consistent[1], 9 );
    ASSERT_EQ( amount_of_every_sequence_consistent[2], 9 );
    for ( int i = 0; i < SIZE; i++ ) free( sequences[i] );
    free( sequences );
}

TEST( parallel, 1st )
{
    typedef void __cdecl (*dll_func)( char ** sequences, int * amount_of_every_sequence, int count, char * filename );
    dll_func number_of_sequences_parallel = NULL;
    HMODULE hDLL = LoadLibrary("../libparallel.dll");
    if (!hDLL) FAIL();
    number_of_sequences_parallel = (dll_func)GetProcAddress(hDLL, "number_of_sequences_parallel");
    if (!number_of_sequences_parallel) FAIL();

    char ** sequences = ( char ** )malloc( SIZE * sizeof( char * ) );

    for( int i = 0; i < SIZE; i++ )
        sequences[i] = ( char * )malloc( sizeof( char ) * SIZE );

    strcpy( sequences[0], ( "aa" ) );
    strcpy( sequences[1], ( "bb" ) );
    strcpy( sequences[2], ( "zz" ) );

    int amount_of_every_sequence_parallel[SIZE];

    number_of_sequences_parallel( sequences, amount_of_every_sequence_parallel, SIZE, (char * ) TESTFILE_1 );

    ASSERT_EQ( amount_of_every_sequence_parallel[0], 3 );
    ASSERT_EQ( amount_of_every_sequence_parallel[1], 0 );
    ASSERT_EQ( amount_of_every_sequence_parallel[2], 0 );
    for ( int i = 0; i < SIZE; i++ ) free( sequences[i] );
    free( sequences );

    FreeLibrary(hDLL);
}

TEST( parallel, 2nd )
{
    typedef void __cdecl (*dll_func)( char ** sequences, int * amount_of_every_sequence, int count, char * filename );
    dll_func number_of_sequences_parallel = NULL;
    HMODULE hDLL = LoadLibrary("../libparallel.dll");
    if (!hDLL) FAIL();
    number_of_sequences_parallel = (dll_func)GetProcAddress(hDLL, "number_of_sequences_parallel");
    if (!number_of_sequences_parallel) FAIL();

    char ** sequences = ( char ** )malloc( SIZE * sizeof( char * ) );

    for( int i = 0; i < SIZE; i++ )
        sequences[i] = ( char * )malloc( sizeof( char ) * SIZE );

    strcpy( sequences[0], ( "Hello" ) );
    strcpy( sequences[1], ( "world" ) );
    strcpy( sequences[2], ( "!" ) );

    int amount_of_every_sequence_parallel[SIZE];

    number_of_sequences_parallel( sequences, amount_of_every_sequence_parallel, SIZE, (char * ) TESTFILE_4 );

    ASSERT_EQ( amount_of_every_sequence_parallel[0], 9 );
    ASSERT_EQ( amount_of_every_sequence_parallel[1], 9 );
    ASSERT_EQ( amount_of_every_sequence_parallel[2], 9 );
    for ( int i = 0; i < SIZE; i++ ) free( sequences[i] );
    free( sequences );

    FreeLibrary(hDLL);
}

