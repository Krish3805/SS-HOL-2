/*
Name : 46.c
Author : Krish Vaghasiya
Description : Write a program to remove the message queue using msgctl
              with the IPC_RMID command.
Date : 23rd Oct, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

int main()
{
    key_t key;
    int msgid;

    key   = ftok("progfile", 65);
    if (key == -1) { perror("ftok"); exit(1); }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) { perror("msgget"); exit(1); }

    printf("Message queue ID before removal: %d\n", msgid);

    /* Remove the message queue */
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID");
        exit(1);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}

/*
Sample Output :

# Compile
~/Hand_On_List2/programs$ gcc 46.c -o 46
~/Hand_On_List2/programs$ touch progfile

# Send a message first (optional):
~/Hand_On_List2/programs$ ./46_sender
Message sent: Hello from sender!

# Check queue:
~/Hand_On_List2/programs$ ipcs -q
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x410f51a4 65536      krish  666        100          1

# Remove queue:
~/Hand_On_List2/programs$ ./46
Message queue ID before removal: 65536
Message queue removed successfully.

# Verify removal:
~/Hand_On_List2/programs$ ipcs -q
------ Message Queues --------
(empty — queue has been removed)

*/
