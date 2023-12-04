#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 256

int main() {
    char *welcome = "Welcome to ENSEA Tiny Shell\n";
    char prompt[BUFFER_SIZE];
    char buffer[BUFFER_SIZE];
    char goodbye[] = "Bye bye...\n";
    int status;

    struct timespec start_time, end_time;
    long elapsed_time;

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

            if (pid != 0) { 
                clock_gettime(CLOCK_MONOTONIC, &start_time);
                waitpid(pid, &status, 0);
                clock_gettime(CLOCK_MONOTONIC, &end_time);

                if (WIFEXITED(status)) {
                    elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000 +
                                   (end_time.tv_nsec - start_time.tv_nsec) / 1000000;

                    snprintf(prompt, sizeof(prompt), "enseash[exit:%d|%ldms]%%", WEXITSTATUS(status), elapsed_time);
                    write(STDOUT_FILENO, prompt, strlen(prompt));
                } else if (WIFSIGNALED(status)) {
                    elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000 +
                                   (end_time.tv_nsec - start_time.tv_nsec) / 1000000;

                    snprintf(prompt, sizeof(prompt), "enseash[sign:%d|%ldms]%%", WTERMSIG(status), elapsed_time);
                    write(STDOUT_FILENO, prompt, strlen(prompt));
                }
            } else {  
                execlp(buffer, buffer, (char *)NULL);

            
                perror("Command execution failed");
                exit(1);
            }
        }
    }

    return 0;
}

