#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 100

// Structure for message queue
struct mesg_buffer {
    long mesg_type;
    char mesg_text[MAX];
} message;

int main() {
    key_t key;
    int msgid;

    // Generate unique key
    key = ftok("progfile", 65);

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;

    // Send
    printf("Write Data: ");
    fgets(message.mesg_text, MAX, stdin);
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Data sent is: %s\n", message.mesg_text);

    // Receive
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Data received is: %s\n", message.mesg_text);

    // Destroy message queue
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
