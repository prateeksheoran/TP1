#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>  
#include <stdlib.h>
#include <time.h>


#define HELLO "Welcome to Shell ENSEA. \nTo exit, type 'exit'.\n"
#define BYE "Bye bye \n"
#define ERR "This command doesn't exist. Are you sure ? \n"


#define REGULAR_PROMPT "enseash %  "
#define EXITED_PROMPT "enseash [exit : "
#define SIGNALED_PROMPT "enseash [sign : "
#define END_PROMPT "] % "


#define MAX_SIZE 128
#define MAX_ARG 10
#define EXIT "exit"


struct background_process {
    int pid;
    struct timespec timestart;
    char * progName;
    struct background_process * next;
};


struct background_process_list {
    int processNumber;
    struct background_process * first;
};





