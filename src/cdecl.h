#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKENS 100
#define MAXTOKENLEN 64
enum type_tag {
    IDENTIFIER,
    QUALIFIER,
    TYPE
};

struct token
{
    char type;
    char string[MAXTOKENLEN];
};

int top = -1;
struct token stack[MAXTOKENS];
struct token this;

#define pop stack[top--]
#define push(s) stack[top++] = s

enum type_tag classify_string(void);
void gettoken(void);

void initialize();
void get_array();
void get_params();
void get_lparen();
void get_ptr_part();
void get_type();
void (*nextstate)(void) = initialize;

