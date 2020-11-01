#ifndef HOMEWORK_2_CONSOLE_COMMUNICATION_H
#define HOMEWORK_2_CONSOLE_COMMUNICATION_H

int count_reading();
void cant_allocate();
void cant_open_file();
void cant_create_thread();
char * sequence_reading( int i );
int choose_method();
void result_output( char * sequence, int amount );
void sequences_reading( char ** sequences, int count );

#endif //HOMEWORK_2_CONSOLE_COMMUNICATION_H
