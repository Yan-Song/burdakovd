#include "stack.c"
#include <string.h>
#define operations "+-*/"
#define digits "0123456789.,"

struct node read_node()
// считать что-нибудь из входного потока
{
        struct node v;
        char c;
        // читаем первый символ, пропуская все пробельные символы перед ним
        if(scanf(" %c", &c)<1) // если прочитать не получилось
        {
            v.typ=-1;
            return v;
        };
        
        return v;		
}

void describe(struct node v)
// для отладки, выдаёт на stderr описание node
{
    if(v.typ==0) fprintf(stderr, "[Number]    %lf\n", v.num);
    else if(v.typ==1) fprintf(stderr, "[Function]  %d\n", v.functionid);
    else if(v.typ==2) fprintf(stderr, "[Operation] %c\n", v.op);
    else if(v.typ==3) fprintf(stderr, "[Скобка]    %c\n", v.op);
    else if(v.typ==-1) fprintf(stderr, "[EOF]\n");
    else fprintf(stderr, "[Unknown]\n");
}

int main(int argc, char** argv)
{
   struct node c;
   do
   {
       c=read_node();
       describe(c);
   } while (c.typ!=-1);
   return 0;    
}
