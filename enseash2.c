#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

int main() {
char *welcome = "Welcome to ENSEA Tiny Shell\n";
char *prompt = "enseash% ";
char buffer[BUFFER_SIZE];

write(STDOUT_FILENO, welcome, strlen(welcome));

while (1) {
write(STDOUT_FILENO, prompt, strlen(prompt));

ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
if (bytesRead == -1) {
perror("Error reading input");
return 1;
}

// Add null terminator
buffer[bytesRead] = '\0';

if (strncmp(buffer, "exit", 4) == 0) {
write(STDOUT_FILENO, "Bye Bye\n", 9);
break;
} else if (strncmp(buffer, "fortune", 7) == 0) {
write(STDOUT_FILENO, welcome, strlen(welcome));
}
}

return 0;
}
