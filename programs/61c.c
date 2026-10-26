/*
Name : 61c.c
Author : Krish Vaghasiya
Description : Write a separate program using the sigaction system call to
              catch the SIGFPE signal (floating-point / arithmetic exception).
Date : 23rd Oct, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int signum)
{
    printf("Caught SIGFPE (signal %d) via sigaction: Divide by zero!\n", signum);
    exit(1);
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("SIGFPE handler (sigaction) registered. Triggering divide-by-zero...\n");

    volatile int x = 0;
    volatile int y = 5 / x;   /* -> SIGFPE */
    (void)y;

    return 0;
}

/*
Sample Output :

# Compile
~/Hand_On_List2/programs$ gcc 27c.c -o 27c

# Run
~/Hand_On_List2/programs$ ./27c
SIGFPE handler (sigaction) registered. Triggering divide-by-zero...
Caught SIGFPE (signal 8) via sigaction: Divide by zero!

*/
