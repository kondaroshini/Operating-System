#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h> 

struct msg_buffer{
    long msg_type;
    char msg[100];
}message;

int main(){
    key_t my_key;
    int msg_id;
    my_key = ftok("progfile", 65);
    msg_id = msgget(my_key, 0666 | IPC_CREAT);
   
    if(msg_id == -1){
        perror("msgget");
        return 1;
    }
    message.msg_type = 1;
    printf("Write Message: ");
    fgets(message.msg, 100, stdin);
    message.msg[strlen(message.msg) - 1] = '\0'; 

    if (msgsnd(msg_id, &message, sizeof(message), 0) == -1) {
        perror("msgsnd");
        return 1;
    }

    printf("Sent Message: %s\n", message.msg);

    if (msgrcv(msg_id, &message, sizeof(message), 1, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Received Message: %s\n", message.msg);

    if (msgctl(msg_id, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }
    return 0;
}

