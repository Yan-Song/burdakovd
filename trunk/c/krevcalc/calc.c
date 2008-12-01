#include "stack.c"
#include <assert.h>
#include "functions.c"
#include <string.h>
#include <math.h>

#define operations "+-*/^"
#define skobki "()"
#define digits "0123456789."
#define maxnumlength 100

struct node read_node()
// считать что-нибудь из входного потока
{
        static char buf=0;
        struct node v;
        char c;
        // читаем первый символ, пропуская все пробельные символы перед ним
        // если он уже прочитан раньше в buf, используем его и очищаем
        if(index(" \n\t", buf)==NULL) // еслм в буфере не пустышка и не 0
        {
            c=buf;
            buf=0;
        }
        else if(scanf(" %c", &c)<1) // если прочитать не получилось
        {
            v.typ=-1;
            return v;
        };
        v.op = c;
        // возможно это число, вызов функции, скобка или операция
        if(index(digits, c)!=NULL)
        {
            v.typ = 0; // число (см. описание node в stack.c)
            char nums[maxnumlength+2];
            nums[0]=c;
            int p=1;
            while((scanf("%c", &c)==1)&&(p<=maxnumlength)) // читаем всё число
            {
                if(index(digits, c)==NULL) // если уже не число
                {
                    buf=c; // сохраняем прочитанное
                    break;
                }
                nums[p++]=c;
            }
            nums[p] = 0; // конец строки
            if(p>maxnumlength)
            {
                fprintf(stderr, "Слишком много цифр: %s...\n", nums);
                v.typ = -2;
            }
            else if(sscanf(nums, "%lf", &v.num)!=1)
            {
                fprintf(stderr, "Неправильное число: %s\n", nums);
                v.typ = -2;
            }
        }
        else if(index(operations, c)!=NULL) // операция
        {
            v.typ = 2;
            v.op = c;
        }
        else if(index(skobki, c)!=NULL) // скобка
        {
            v.typ = 3;
            v.op = c;
        }
        else if((c>='a')&&(c<='z')) // вызов функции
        {
            v.typ = 1;
            char fname[maxfnnamelength+3];
            fname[0] = c;
            int p=1;
            while((scanf("%c", &c)==1)&&(p<=maxfnnamelength))
            {
                if((c>'z')||(c<'a')) // если уже не буква
                {
                    buf=c; // сохраняем прочитанное
                    break;
                }
                fname[p++]=c;
            }
            fname[p] = 0; // конец строки
            if(p>maxfnnamelength)
            {
                fprintf(stderr, "Слишком длинное имя функции: %s...\n", fname);
                v.typ = -2;
            }
            else
            {
                v.function = find_function(fname);
                if(v.function==NULL)
                {
                    fprintf(stderr, "Нет такой функции: %s\n", fname);
                    v.typ = -2;
                }
            }
        }
        else
        {
            fprintf(stderr, "Непонятный символ: '%c'\n", c);
            v.typ = -2;
        }
        return v;		
}

void describe(struct node v)
// для отладки, выдаёт на stderr описание node
{
    if(v.typ==0)       fprintf(stderr, "[Число]    %lf\n", v.num);
    else if(v.typ==1)  fprintf(stderr, "[Функция]  %d\n", v.function);
    else if(v.typ==2)  fprintf(stderr, "[Оператор] %c\n", v.op);
    else if(v.typ==3)  fprintf(stderr, "[Скобка]   %c\n", v.op);
    else if(v.typ==-1) fprintf(stderr, "[EOF]\n");
    else if(v.typ==-2) fprintf(stderr, "[Ошибка]\n");
    else               fprintf(stderr, "[что-то] l %c\n", v.op);
}

int priority(char op)
{
    if(op=='+') return 1;
    else if (op=='-') return 1;
    else if (op=='*') return 2;
    else if (op=='/') return 2;
    else if (op=='^') return 3;
    else assert(0);
}

double do_operator(char op, double arg1, double arg2)
{
    if(op=='-') return arg1-arg2;
    else if(op=='+') return arg1+arg2;
    else if(op=='/') return arg1/arg2;
    else if(op=='*') return arg1*arg2;
    else if(op=='^') return pow(arg1,arg2);
    else assert(0);
}

void do_opz(stack* s, struct node op)
// производит операцию op на числовым стеком stack
{
    //fprintf(stderr, "%s\n", "do_opz started");
    if(op.typ==1)
    {
        struct node _;
        if (isEmpty(*s))
        {
            fprintf(stderr, "Недостаточно аргументов для использования функции %s.\n", op.function->name);
            exit(1);
        }
        _.num = (op.function->handler)(pop(s).num); // вызов функции
        push(s, _);
    }
    else if(op.typ==2)
    {
        //fprintf(stderr, "%s\n", "do_opz op.typ=2");
        double arg2;
        if(!isEmpty(*s))
            arg2=pop(s).num;
        if(isEmpty(*s))
        {
            fprintf(stderr, "Недостаточно аргументов для использования оператора '%c'.\n", op.op);
            exit(1);
        }
        double arg1=pop(s).num;
        //fprintf(stderr, "arg1=%lf, arg2=%lf\n", arg1, arg2);
        struct node _;
        _.num = do_operator(op.op, arg1, arg2);
        push(s, _);
    }
    else assert(0);
}

int calc(int OPZ)
// используется алгоритм преобразования из инфиксной нотации, как описано
// в http://ru.wikipedia.org/wiki/Обратная_польская_запись, но
// вычисления производятся в процессе преобразования, таким образом, что в стеке ОПЗ хранятся только числа,
// а операции производятся "на месте"
{
   struct node c;
   int minusIsUnary=1;
   stack opz=emptyStack();
   stack tmp=emptyStack();
   do
   {
   	 
       c=read_node();
       //describe(c);
       if(c.typ==-1) // EOF
           while(!isEmpty(tmp))
            {
                struct node _=pop(&tmp);
                if(_.typ!=3) // не скобка
                    do_opz(&opz, _); // доделываем
                else
                {
                    fprintf(stderr, "В выражении несогласованы скобки. (Вероятно не хватает закрывающей скобки)\n");
                    exit(1);
                }
            }
       else if(c.typ==-2) break; // ошибка
       else if(OPZ) // это если нам на вход уже подают данные в ОПЗ
       {
           if(c.typ==0) push(&opz, c);
           else if(c.typ==1) do_opz(&opz, c);
           else if(c.typ==2) do_opz(&opz, c);
           else if(c.typ==3)
           {
               fprintf(stderr, "В ОПЗ нельзя использовать скобки\n");
               exit(1);
           }
           else assert(0);
       }
       else // http://ru.wikipedia.org/wiki/Обратная_польская_запись , Преобразование из инфиксной нотации
       {
       	  // хаки для работы унарного минуса
       	  if((c.typ==2)&&(c.op=='-')&&(minusIsUnary>0))
       	  {
       	      c.typ=1;
       	      c.function=find_function("<operator 'unary minus'>");
       	  }
           if(c.typ==0) push(&opz, c); // число
           else if(c.typ==1) push(&tmp, c); // function
           else if(c.typ==2) // оператор
           {
               int prio=priority(c.op);
               while((!isEmpty(tmp)) && ( // стек не пуст и...
                      (head(tmp).typ==1)|| // там функция или
                       ((head(tmp).typ==2)&&(priority(head(tmp).op)>=prio)))) // или оператор с немЕньшим приоритетом
                   // выполняем их их в opz
                   do_opz(&opz, pop(&tmp));
               push(&tmp, c);
           }
           else if(c.typ==3)
               if(c.op=='(') push(&tmp, c);
               else // ')'
               {
                   while((!isEmpty(tmp)) &&  // стек не пуст и...
                           (head(tmp).typ!=3)) // ...и не дошли до '('
                       do_opz(&opz, pop(&tmp)); // выполняем всё из стека
                   if(isEmpty(tmp)) // если дошли до конца стека и не встретили '('
                   {
                       fprintf(stderr, "В выражении несогласованы скобки. (Вероятно лишняя закрывающая скобка)\n");
                       exit(1);
                   }
                   //printf("%s", "pop'ed '('\n");
                   pop(&tmp); // иначе выкидываем '('
               }
       }
     if(((c.typ==3)&&(c.op=='('))||(c.typ==1)) minusIsUnary=1;
     else minusIsUnary=0;
   } while (c.typ>=0);
   if(c.typ==-2)
   {
       fprintf(stderr, "Ошибка ввода. Вычисление прервано.\n");
       exit(1);
   }
   else if(c.typ==-1)
   {
       if(isEmpty(opz))
       {
           fprintf(stderr, "Стек пуст.\n");
           exit(1);
       }
       struct node _=pop(&opz);
       if(!isEmpty(opz))
       {
           fprintf(stderr, "В стеке больше одного числа, вероятно ошибка в выражении\n");
           exit(1);
       }
       printf("%.9lf\n", _.num);
       exit(0);
   }
   fprintf(stderr, "Случилось невозможное.\n");
   exit(1);
}

int main(int argc, char* argv[])
{
    if((argc>1)&&(strcmp(argv[1], "opz")==0)) calc(1);
    else calc(0);
    fprintf(stderr, "Случилось невозможное.\n");
    exit(1);
}
