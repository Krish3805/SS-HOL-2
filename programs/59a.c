/*
Name : 59a.c
Author : Krish Vaghasiya
Description : Write a separate program using the signal system call to catch
              the SIGSEGV signal (segmentation fault - invalid memory access).
Date : 23rd Oct, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void segv_handler(int signum)
{
    printf("Caught SIGSEGV (signal %d): Invalid memory access!\n", signum);
    exit(1);
}

int main()
{
    signal(SIGSEGV, segv_handler);

    printf("Registered SIGSEGV handler. Triggering segfault...\n");

    int *p = NULL;
    *p = 100;   /* Dereference NULL pointer -> SIGSEGV */

    return 0;
}

/*
Sample Output :

# Compile
~/Hand_On_List2/programs$ gcc 25a.c -o 25a

# Run
~/Hand_On_List2/programs$ ./25a
Registered SIGSEGV handler. Triggering segfault...
Caught SIGSEGV (signal 11): Invalid memory access!

*/
