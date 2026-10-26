/*
Name : 41.c
Author : Krish Vaghasiya
Description : Write a program to create a message queue, and print the key
              and message queue ID.
Date : 23rd Oct, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main()
{
    key_t key;
    int msgid;

    /* Generate a unique key using a project file and project id */
    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    /* Create the message queue with read/write permissions */
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message Queue Key : %d\n", key);
    printf("Message Queue ID  : %d\n", msgid);

    return 0;
}

/*
Sample Output :

# Compile
~/Hand_On_List2/programs$ gcc 41.c -o 41

# Create a key file first
~/Hand_On_List2/programs$ touch progfile

# Run
~/Hand_On_List2/programs$ ./41
Message Queue Key : 1091655841
Message Queue ID  : 65536

# Verify with ipcs
~/Hand_On_List2/programs$ ipcs -q

(Key and ID values are runtime-dependent.)

# Remove the queue after use
~/Hand_On_List2/programs$ ipcrm -q 65536

*/
