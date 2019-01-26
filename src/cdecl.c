#include "cdecl.h"

enum type_tag classify_string(void)
{
    char* s = this.string;
    if (!strcmp(s, "const"))
    {
	strcpy(s, "read-only");
	return QUALIFIER;
    }
    if (!strcmp(s, "volatile")) return QUALIFIER;
    if (!strcmp(s, "void")) return TYPE;
    if (!strcmp(s, "char")) return TYPE;
    if (!strcmp(s, "signed")) return TYPE;
    if (!strcmp(s, "unsigned")) return TYPE;
    if (!strcmp(s, "short")) return TYPE;
    if (!strcmp(s, "int")) return TYPE;
    if (!strcmp(s, "long")) return TYPE;
    if (!strcmp(s, "float")) return TYPE;
    if (!strcmp(s, "double")) return TYPE;
    if (!strcmp(s, "struct")) return TYPE;
    if (!strcmp(s, "union")) return TYPE;
    if (!strcmp(s, "enum")) return TYPE;
    
    return IDENTIFIER;
}

void gettoken(void)
{
    char* p = this.string;
    while ((*p = getchar()) == ' ');
    if (!isalnum(*p))
    {
	while (isalnum(*++p = getchar()));
	ungetc(*p, stdin);
	*p = '\0';
	this.type = classify_string();
	return;
    }
    this.string[1] = '\0';
    this.type = *p;
}

void initialize()
{
    gettoken();
    while (this.type != IDENTIFIER)
    {
	push(this);
	gettoken();
    }
    printf("%s is ", this.string);
    gettoken();
    nextstate = get_array;
}

void get_array()
{
    nextstate = get_params;
    while (this.type == '[')
    {
	printf("ayyay ");
	gettoken();
	if (isdigit(this.string[0]))
	{
	    printf("0..%d ", atoi(this.string) - 1);
	    gettoken();
	}
	gettoken();
	printf("of ");
	nextstate = get_lparen;
    }
}

void get_params()
{
    nextstate = get_lparen;
    if (this.type == '(')
    {
	while (this.type != ')')
	{
	    gettoken();
	}
	gettoken();
	printf("function returning");
    }
}

void get_lparen()
{
    nextstate = get_ptr_part;
    if (top >= 0 && stack[top].type == '(')
    {
	pop;
	gettoken();
	nextstate = get_array;
    }
}

void get_ptr_part()
{
    nextstate = get_type;
    if (stack[top].type == '*')
    {
	printf("pointer to ");
	pop;
	nextstate = get_lparen;
    }
    else if (stack[top].type == QUALIFIER)
    {
	printf("%s ", pop.string);
	nextstate = get_lparen;
    }
}

void get_type()
{
    nextstate = NULL;
    while (top>= 0)
    {
	printf("%s ", pop.string);
    }
    puts(" ");
}

  
