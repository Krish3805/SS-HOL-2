/*
Name : 61b.c
Author : Krish Vaghasiya
Description : Write a separate program using the sigaction system call to
              catch the SIGINT signal (Ctrl+C interrupt).
Date : 23rd Oct, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum)
{
    printf("\nCaught SIGINT (signal %d) via sigaction!\n", signum);
    exit(0);
}

int main()
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("SIGINT handler (sigaction) registered. Press Ctrl+C...\n");

    while (1) {
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}

/*
Sample Output :

# Compile
~/Hand_On_List2/programs$ gcc 27b.c -o 27b

# Run
~/Hand_On_List2/programs$ ./27b
SIGINT handler (sigaction) registered. Press Ctrl+C...
Running...
Running...
^C
Caught SIGINT (signal 2) via sigaction!

*/
