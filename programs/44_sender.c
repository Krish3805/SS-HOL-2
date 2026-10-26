
/*
Name : 44_sender.c
Author : Krish Vaghasiya
Description : Helper program for Exercise 44. Sends one message to the
              message queue so that 44a.c and 44b.c can receive it.
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
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello from sender!");
    msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    printf("Message sent: %s\n", message.msg_text);

    return 0;
}

/*
Sample Output :

~/Hand_On_List2/programs$ ./44_sender
Message sent: Hello from sender!

*/
