#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h> 
#include <string.h>
#define FIFO_NAME "myfifo"

int main(){
    int ret;
    char data[] = "Hello, named pipe!";
    char receivedData[100];
    ret = mkfifo(FIFO_NAME, 0666);
    if(ret == -1){
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }
   
    printf("Named pipe created.\n");
    pid_t pid = fork();
    if(pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if(pid == 0) {
        int fd = open(FIFO_NAME, O_WRONLY);
        if(fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        ret = write(fd, data, strlen(data));
        if(ret == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        printf("Data written to the named pipe.\n");
        close(fd);
        exit(EXIT_SUCCESS);
    } 
    else {
        int fd = open(FIFO_NAME, O_RDONLY);
        if(fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
        ret = read(fd,receivedData, sizeof(receivedData));
        if(ret == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("Received data from the named pipe: %s\n", receivedData);
        close(fd);
        wait(NULL);
        unlink(FIFO_NAME);
        printf("Named pipe removed.\n");
        exit(EXIT_SUCCESS);
    }
}
