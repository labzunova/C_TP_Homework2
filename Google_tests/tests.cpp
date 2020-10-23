#include "gtest/gtest.h"
extern "C" {
#include "../parallel/parallel_realization.h"
#include "../consistent/consistent_realization.h"
}
#define SEQUENCE_1 "aa"
#define SEQUENCE_2 "bb"
#define SEQUENCE_3 "zz"
#define SIZE 3

TEST( compresstion, 3_sequences )
{
   //char ** sequences = ( char ** ) malloc(SIZE * sizeof( char * ) + SIZE * SIZE * sizeof ( char * ) ) ;

    char ** sequences = ( char ** ) malloc(SIZE     * sizeof( char * ) );

    sequences[0] = ( char * )malloc( sizeof( char ) * 10 );
    sequences[1] = ( char * )malloc( sizeof( char ) * 10 );
    sequences[2] = ( char * )malloc( sizeof( char ) * 10 );

    strcpy( sequences[0], ( char * )( SEQUENCE_1 ) );
    strcpy( sequences[1], ( char * )( SEQUENCE_2 ) );
    strcpy( sequences[2], ( char * )( SEQUENCE_3 ) );

    int amount_of_every_sequence_parallel[3];
    int amount_of_every_sequence_consistent[3];
    number_of_sequences( sequences, amount_of_every_sequence_consistent, 3 );
    number_of_sequences_parallel( sequences, amount_of_every_sequence_parallel, 3 );


    for ( int i = 0; i < 3; i++ )
        ASSERT_EQ( amount_of_every_sequence_consistent[i].price, amount_of_every_sequence_parallel[i] );
    free( sequences );
}

TEST( compresstion, file_100mb )
{

    ASSERT_EQ( 1, 1 );
}

TEST( compresstion, stress )
{

    ASSERT_EQ( 1, 1 );
}