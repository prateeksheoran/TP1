#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 1024

void displayWelcomeMessage() {
    const char welcomeMessage[] = "Welcome to ENSEA tiny shell. Type 'exit' to quit.\n";
    write(STDOUT_FILENO, welcomeMessage, sizeof(welcomeMessage) - 1);
}

void displayPrompt() {
    const char prompt[] = "enseash> ";
    write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

int main() {
    char input[MAX_INPUT_SIZE];

    displayWelcomeMessage();

    while (1) {
        displayPrompt();

        ssize_t bytesRead = read(STDIN_FILENO, input, sizeof(input));

        if (bytesRead == 0) {
            // Handle EOF (Ctrl+D)
            write(STDOUT_FILENO, "\n", 1);
            break;
        // Remove newline character at the end
        input[strcspn(input, "\n")] = '\0';

        // Exit the shell if the user enters "exit"
        if (strcmp(input, "exit") == 0) {
            break;
        }
    }

    return 0;
}
}
