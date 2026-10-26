/*
Name : 43.c
Author : Krish Vaghasiya
Description : Write a program to send messages to the message queue.
              After sending, verify using the shell command: ipcs -q
Date : 23rd Oct, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main()
{
    key_t key;
    int msgid;
    struct msg_buffer message;

    key   = ftok("progfile", 65);
    if (key == -1) { perror("ftok"); exit(1); }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) { perror("msgget"); exit(1); }

    message.msg_type = 1;
    strcpy(message.msg_text, "Hello from sender!");

    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent: %s\n", message.msg_text);
    printf("Use 'ipcs -q' to verify the message queue.\n");

    return 0;
}

/*
Sample Output :

# Compile
~/Hand_On_List2/programs$ gcc 43.c -o 43
~/Hand_On_List2/programs$ touch progfile

# Run
~/Hand_On_List2/programs$ ./43
Message sent: Hello from sender!
Use 'ipcs -q' to verify the message queue.

# Verify
~/Hand_On_List2/programs$ ipcs -q
------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages
0x410f51a4 65536      krish  666        100          1

# Remove queue after use
~/Hand_On_List2/programs$ ipcrm -q 65536

*/
