/*
Name : 39_writer.c
Author : Krish Vaghasiya
Description : Companion writer program for Exercise 39.
              Writes a message into the FIFO 'select_fifo' so that 9.c
              can receive it via the select system call.
Date : 23rd Oct, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_NAME "select_fifo"

int main()
{
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char *message = "Hello from writer process!";
    write(fd, message, strlen(message));
    close(fd);

    printf("Writer: message sent to FIFO.\n");

    return 0;
}

/*
Sample Output :

~/Hand_On_List2/programs$ ./39_writer
Writer: message sent to FIFO.

*/
