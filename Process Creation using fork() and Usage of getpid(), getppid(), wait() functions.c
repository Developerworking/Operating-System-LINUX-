#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    // Create a child process
    pid = fork();

    if (pid < 0) { // Error occurred
        perror("Fork failed");
        return 1;
    } else if (pid == 0) { // Child process
        printf("Child process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        printf("Child process is running...\n");
        sleep(2); // Simulate some work
        printf("Child process is exiting...\n");
        exit(0);
    } else { // Parent process
        printf("Parent process:\n");
        printf("PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
        printf("Parent is waiting for child to finish...\n");

        // Wait for the child process to complete
        wait(NULL);

        printf("Child process has finished. Parent process is exiting...\n");
    }

    return 0;
}
