#include <string.h>
#define maxfnnamelength 100
#define function_count 1

#ifndef KREVCALCF
#define KREVCALCF

struct func
{
    char name[maxfnnamelength+3];
    double (* handler)( );
};


// BEGIN LIBRARY

double sqr(double x)
{
    return x*x;
}

// END LIBRARY


struct func library[function_count] = {{"sqr", &sqr}};

struct func* find_function(char* name)
{
    int i;
    for(i=0; i<function_count; i++)
        if(strcmp(name, library[i].name)==0)
            return &(library[i]);
    return NULL;
}

#endif
