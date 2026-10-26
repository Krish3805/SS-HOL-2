/*
Name : 49d.c
Author : Krish Vaghasiya
Description : Write a program to remove the created semaphore using semctl
              with the IPC_RMID command.
Date : 23rd Oct, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#ifndef __APPLE__
union semun { int val; struct semid_ds *buf; unsigned short *array; };
#endif

int main()
{
    key_t key  = ftok("semfile", 65);
    int semid  = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) { perror("semget"); exit(1); }

    /* Initialize to 1 so it shows up in ipcs -s */
    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    printf("Semaphore created. ID = %d\n", semid);
    printf("Use 'ipcs -s' to verify it exists.\n");

    /* Remove semaphore */
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(1);
    }

    printf("Semaphore (ID=%d) removed successfully.\n", semid);
    printf("Use 'ipcs -s' to verify it is gone.\n");

    return 0;
}

/*
Sample Output :

# Compile
~/Hand_On_List2/programs$ gcc 31d.c -o 31d
~/Hand_On_List2/programs$ touch semfile

# Run
~/Hand_On_List2/programs$ ./31d
Semaphore created. ID = 65536

# Verify it exists
~/Hand_On_List2/programs$ ipcs -s
------ Semaphore Arrays --------
key        semid      owner   ...
0x410f51a4 65536      krish ...

Semaphore (ID=65536) removed successfully.

# Verify it's gone
~/Hand_On_List2/programs$ ipcs -s
------ Semaphore Arrays --------
(empty)

*/
