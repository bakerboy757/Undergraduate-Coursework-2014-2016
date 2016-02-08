#include "types.h"
#include "user.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"

void sort(struct uproc *, int);
char *getstate(int);
int main()
{
    int max = 2, i, proccount;
    char state[16];
    struct uproc *table = malloc(max * sizeof(struct uproc));
    proccount = getprocs(max, table);
    if(proccount < 0){
       printf(0, "Error");
       exit();
    }
    //reallocate space for table if there are more processes than we anticipated
    if(proccount > max){
       free(table);
       max = proccount;
       table = malloc(max * sizeof(struct uproc));
       proccount = getprocs(max, table);
    }
    //sort uprocs by size
    sort(table, proccount);
    for(i = 0; i < proccount; i++){
       //gets enum type and translates to char
       strcpy(state, getstate(table[i].state));
       printf(0, "%d  %s  %d  %s\n", table[i].pid, state, table[i].sz, table[i].name);
    }
   exit();
}
char *getstate(int num){
   if(num == 0)
      return "UNUSED";
   if(num == 1)
      return "EMBRYO";
   if(num == 2)
      return "SLEEPING";
   if(num == 3)
      return "RUNNABLE";
   if(num == 4)
      return "RUNNING";
   if(num == 5)
      return "ZOMBIE";

   return "INVALID";
}
void sort(struct uproc *table, int max){
   int i, j;
   struct uproc temp;
   for(i = 0; i < max; i++){
      for(j = i+1; j < max; j++){
         if(table[i].sz < table[j].sz){
            temp = table[i];
            table[i] = table[j];
            table[j] = temp;
         }
         if(table[i].sz == table[j].sz){
            

         }
      }
   }
}
