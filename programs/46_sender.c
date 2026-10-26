/*
Name : 46_sender.c
Author : Krish Vaghasiya
Description : Helper sender for Exercise 46. Creates queue and sends a message.
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
    key_t key   = ftok("progfile", 65);
    int   msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg_buffer message;
    message.msg_type = 1;
    strcpy(message.msg_text, "Hello from sender!");
    msgsnd(msgid, &message, sizeof(message.msg_text), 0);
    printf("Message sent: %s\n", message.msg_text);
    return 0;
}

/*
Sample Output :

~/Hand_On_List2/programs$ ./46_sender
Message sent: Hello from sender!

*/
