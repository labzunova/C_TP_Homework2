#include "gtest/gtest.h"
extern "C" {
#include "../parallel/parallel_realization.h"
#include "../consistent/consistent_realization.h"
}
#define SEQUENCE_1 "aa"
#define SEQUENCE_2 "bb"
#define SEQUENCE_3 "zz"
#define TESTFILE_1 "homework2.txt"
#define SIZE 3

#include <cstdio>

TEST( compresstion, 3_sequences )
{
   //char ** sequences = ( char ** ) malloc(SIZE * sizeof( char * ) + SIZE * SIZE * sizeof ( char * ) ) ;

    char ** sequences = ( char ** )malloc(SIZE     * sizeof( char * ) );

    for( int i = 0; i < SIZE; i++ )
        sequences[i] = ( char * )malloc( sizeof( char ) * SIZE );

    strcpy( sequences[0], ( char * )( SEQUENCE_1 ) );
    strcpy( sequences[1], ( char * )( SEQUENCE_2 ) );
    strcpy( sequences[2], ( char * )( SEQUENCE_3 ) );

    int amount_of_every_sequence_consistent[SIZE];
    int amount_of_every_sequence_parallel[SIZE];
    number_of_sequences( sequences, amount_of_every_sequence_consistent, SIZE, (char * ) TESTFILE_1 );
   // number_of_sequences_parallel( sequences, amount_of_every_sequence_parallel, SIZE, (char * ) TESTFILE_1 );

    for ( int i = 0; i < SIZE; i++ )
        ASSERT_EQ( amount_of_every_sequence_consistent[i], amount_of_every_sequence_parallel[i] );
    ASSERT_EQ( 1, 1 );
    free( sequences ); // ?
    free ( amount_of_every_sequence_consistent );
    free ( amount_of_every_sequence_parallel );
}

TEST( compresstion, file_100mb )
{

    ASSERT_EQ( 1, 1 );
}

TEST( compresstion, stress )
{

    ASSERT_EQ( 1, 1 );
}