#include <stdio.h>

int main ()
{
    char sentence []="January 14, 2008 08:59\0";
    char str [20];
    char month[60];
    int day, year, hours, minutes;

    sscanf (sentence,"%s %d%*c %d %d%*c%d",month, &day, &year, &hours, &minutes);
    printf ("%d|%s|%d|%d|%d\n", year, month, day, hours, minutes);
  
    return 0;
}
