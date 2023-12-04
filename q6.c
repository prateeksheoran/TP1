
#include "functions.h"


int main(void){
    char commande[MAX_SIZE] = {0};
    char display[MAX_SIZE] = {0};
    int commande_size;
    int pid;
    int status;
    int test;
    struct timespec timestart;
    struct timespec timestop;
   
   
   // Welcome message
    write(STDOUT_FILENO, HELLO, strlen(HELLO));
    write(STDOUT_FILENO, REGULAR_PROMPT, strlen(REGULAR_PROMPT));
   
    while(1){
        
        commande_size = read(STDOUT_FILENO, commande, MAX_SIZE);
       
       
        commande[commande_size-1] = '\0';
        
        //exit the process with the "exit" or ctrl+d command
        test = strcmp(EXIT, commande);
        if(test==0 || commande_size==0){
            write(STDOUT_FILENO, BYE, strlen(BYE));
            kill(getpid(),SIGINT);
        }
       
        clock_gettime(CLOCK_REALTIME, &timestart);
       
        pid = fork();
        if(pid==0){
           //Child process
            //execlp("hostname", "hsotname", "-i", NULL) //very complicated because you would have to count the number of arguments to know which one you pass --> so we use execvp with an array
            char * argv[MAX_ARG]={NULL};
            int i = 0;
           
            
            argv[0] = strtok(commande, " ");
           
           
            while (argv[i] != NULL){
                i++;
                argv[i] = strtok(NULL, " ");
            }
            execvp(argv[0], argv);
           
           
            write(STDOUT_FILENO, ERR, strlen(ERR));
            kill(getpid(),SIGINT);
        } else {
            //parent process
            wait(&status);
            clock_gettime(CLOCK_REALTIME, &timestop);
            int time = (timestop.tv_nsec - timestart.tv_nsec)/1000000;
            if(WIFSIGNALED(status)){
                sprintf(display, "%s%d%s%d%s%s", SIGNALED_PROMPT, WSTOPSIG(status), "|", time, "ms", END_PROMPT);
                write(STDOUT_FILENO, display, strlen(display));
            } else {
                if(WIFEXITED(status)){
                    sprintf(display, "%s%d%s%d%s%s", EXITED_PROMPT, WSTOPSIG(status), "|", time, "ms", END_PROMPT);
                    write(STDOUT_FILENO, display, strlen(display));
                }
            }
        }
    }  
}



