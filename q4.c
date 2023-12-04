#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define BUFFER_SIZE 256

int main() {
    char *welcome = "Welcome to ENSEA Tiny Shell\n";
    char prompt[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    char goodbye[] = "Bye bye...\n";
    int status;

    while (1) {
        write(STDOUT_FILENO, "enseash%", 8);

        ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (bytesRead <= 0) {
            write(STDOUT_FILENO, goodbye, strlen(goodbye));
            break;
        }


        if (buffer[bytesRead - 1] == '\n') {
            buffer[bytesRead - 1] = '\0';
        }

        if (strncmp(buffer, "fortune", 7) == 0) {
            write(STDOUT_FILENO, welcome, strlen(welcome));
        } else {
            
            if (strcmp(buffer, "exit") == 0) {
                write(STDOUT_FILENO, goodbye, strlen(goodbye));
                break;
            }

            int pid = fork();

            if (pid != 0) {  // Parent process
                waitpid(pid, &status, 0);

                
                snprintf(prompt, sizeof(prompt), "enseash[exit:%d]%%", WEXITSTATUS(status));
                write(STDOUT_FILENO, prompt, strlen(prompt));
            } else {  // Child process
                execlp(buffer, buffer, (char *)NULL);

                // If execlp fails, print an error message
                perror("Command execution failed");
                exit(1);
            }
        }
    }

    return 0;
}


