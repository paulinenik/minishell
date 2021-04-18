#include<stdlib.h>
#include<stdio.h>
#include "unistd.h"

int main(void)
{
   char *s;
   s = getenv("HOME"); /* получить параметр среды */
   printf("Командный процессор находится: %d\n", ttyslot());
   return 0;
}
