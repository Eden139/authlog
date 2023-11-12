#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

typedef struct {
	char* name;
	char* datetime;
	char* session;
	char* status;
} Auth;

int count_line (FILE* stream);
void write_head(void);
void write_css(void);
void write_body(FILE* auth);
Auth* get_users(FILE* auth, int count, int* user_number, char* user);
void write_table(Auth* session, int* user_number, int page, char* user);
int min(int a, int b);
void to_gasy(char* date);

#endif
