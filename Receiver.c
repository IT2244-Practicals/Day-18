#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main() {
    key_t key;
    int msgid;

    // Generate unique key
    key = ftok("progfile", 65);

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Data received is: %s\n", message.mesg_text);

    // Destroy message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
