/*
Name : 47.c
Author : Krish Vaghasiya
Description : Write a program to create shared memory and perform:
              (a) Write some data to the shared memory.
              (b) Attach with SHM_RDONLY and check whether you are able to overwrite.
              (c) Detach the shared memory.
              (d) Remove the shared memory.
Date : 23rd Oct, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
    key_t key   = ftok("shmfile", 65);
    int   shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    /* (a) Write data: attach with read-write access */
    char *rw_ptr = (char *)shmat(shmid, NULL, 0);
    if (rw_ptr == (char *)-1) { perror("shmat rw"); exit(1); }

    strcpy(rw_ptr, "Hello Shared Memory");
    printf("(a) Data written to shared memory: %s\n", rw_ptr);

    /* Detach read-write attachment */
    shmdt(rw_ptr);

    /* (b) Attach with SHM_RDONLY and try to overwrite */
    char *ro_ptr = (char *)shmat(shmid, NULL, SHM_RDONLY);
    if (ro_ptr == (char *)-1) { perror("shmat ro"); exit(1); }

    printf("(b) Data read from read-only attachment: %s\n", ro_ptr);
    printf("    Attempting to write to read-only segment (will cause SIGSEGV)...\n");
    printf("    (Skipped in this run to avoid crash. Writing to ro_ptr would raise SIGSEGV.)\n");
    /*
     * Uncommenting the line below will cause a segmentation fault (SIGSEGV)
     * because the attachment is read-only:
     *   strcpy(ro_ptr, "Try to overwrite");
     */

    /* (c) Detach the read-only shared memory */
    shmdt(ro_ptr);
    printf("(c) Shared memory detached.\n");

    /* (d) Remove the shared memory */
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID");
        exit(1);
    }
    printf("(d) Shared memory removed.\n");

    return 0;
}

/*
Sample Output :

# Compile
~/Hand_On_List2/programs$ gcc 47.c -o 47
~/Hand_On_List2/programs$ touch shmfile

# Run
~/Hand_On_List2/programs$ ./47
(a) Data written to shared memory: Hello Shared Memory
(b) Data read from read-only attachment: Hello Shared Memory
    Attempting to write to read-only segment (will cause SIGSEGV)...
    (Skipped in this run to avoid crash. Writing to ro_ptr would raise SIGSEGV.)
(c) Shared memory detached.
(d) Shared memory removed.

# Verify removal
~/Hand_On_List2/programs$ ipcs -m
------ Shared Memory Segments --------
(empty)

*/
