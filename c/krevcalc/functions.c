#include <string.h>
#include <math.h>
#define maxfnnamelength 100
#define function_count 7

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

double fact(double x)
// should use only for integers
{
    int p=1, i;
    for(i=2; i<=x+0.5; i++)
        p *= i;
    return p;
}

// END LIBRARY


struct func library[function_count] = {
    {"sqr", &sqr},
    {"sqrt", &sqrt},
    {"sin", &sin},
    {"cos", &cos},
    {"tan", &tan},
    {"tg", &tan},
    {"fact", &fact},
//    {"sin", &sin},
};

struct func* find_function(char* name)
{
    int i;
    for(i=0; i<function_count; i++)
        if(strcmp(name, library[i].name)==0)
            return &(library[i]);
    return NULL;
}

#endif
