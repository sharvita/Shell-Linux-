//
//  main.cpp
//  OSlab2
//
//  Created by Sharvita Paithankar on 4/3/19.
//  Copyright © 2019 Sharvita Paithankar. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


//this array stores all the commands into it by using tokenizer
static char* args[512];
pid_t pid; //pid variable
int command_pipe[2];  //two pipes are created
static void waiting(int n); //waits


//This function takes in the input from the user
//It also creates pipe and it forks the process
//This helps with calling the parent process
//Other than that, this function uses execvp()
//which
static int command(int input, int first, int last)
{
    
    
    int fd[2];
    int flag=0;
    pipe(fd);
    //forking the process
    pid = fork();
    
    if (pid == 0) { //fist process
        for(int i=0;args[i]!=0;i++)
        {
            if(args[i][0]=='>')
            {
                fd[1]=open(args[i+1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
                flag=1;
            }
        }
        //uses dup to pipe
        if (first == 1 && last == 0 && input == 0) {
            dup2( fd[1], 1 );
        }
        else if (first == 0 && last == 0 && input != 0) {
            dup2(input, 0);
            dup2(fd[1], 1);
        } else {
        //if this is one then use the fd[1]
            if(flag==1)
            {
                dup2(fd[1],1);
            }
            dup2( input, 0 );
        }
        
        //these if statements check if any of them need to make new file
        if(flag==1)
        {
            if(strcmp(args[1],">>")==0)
                execlp(args[0], args[0], 0, (char *)0);
            else if(strcmp(args[1],">")==0)
                execlp(args[0], args[0], 0, (char *)0);
            else
                execlp(args[0], args[0], args[1], (char *)0);
        }
        else if (execvp( args[0], args) == -1)
            exit(1);
    }

    //if input is 0 then stop process
    if (input != 0)
        close(input);
    close(fd[1]);
    if (last == 1)
        close(fd[0]);
    return fd[0];
}

//prototypes
static int run(char* cmd, int input, int first, int last);
static char line[1024];
static int n = 0;

int main()
{
    printf("MyShell! Type 'exit' to exit.\n");
    while (1) {

        printf("myshell> ");
        fflush(NULL);
        
        //takes in the input
        if (!fgets(line, 1024, stdin))
            return 0;

        int input = 0;
        int first = 1;  //starts at the beginning

        char* cmd = line;
        char* next = strchr(cmd, '|');   //checks if there are multiple commands

        while (next != NULL) {

            *next = '\0';   //moves to next as long as not null
            input = run(cmd, input, first, 0);

            cmd = next + 1;             //next command
            next = strchr(cmd, '|');
            first = 0;
        }
        input = run(cmd, input, first, 1);      //runs the file
        waiting(n);
        n = 0;
        sleep(1);
    }
    return 0;
}

static void parseInputs(char* cmd);  //prototype

//this runs the process and allows the user to change the
//directory or exit it
static int run(char* cmd, int input, int first, int last)
{
    parseInputs(cmd);          //parse the input
    char *directory;        //storing directory
    if (args[0] != NULL) {              //exiting function
        if (strcmp(args[0], "exit") == 0)
            exit(0);
        else if(strcmp(args[0], "cd") == 0)     //using cd command to change directory
        {
            directory = args[1];
            chdir(directory);
            if(chdir(directory) == -1)         //if directory is not avavilable
            {
                fprintf(stderr, "vsh: Error changing directory\n");
            }
        }
        n += 1;
        return command(input, first, last);         //goes through the command again
    }
    return 0;
}

//this function allows the user to skip spaces
static char* skipspace(char* s)
{
    while (isspace(*s)) ++s;
    return s;
}

//this function allows the function to parse
//the input and put it into different places
//in the array
static void parseInputs(char* cmd)
{
    //comman removes spaces
    cmd = skipspace(cmd);
    char* next = strchr(cmd, ' ');
    int i = 0;

    //checks until something is null, removes all unneeded stuff
    while(next != NULL) {
        next[0] = '\0';
        args[i] = cmd;
        ++i;
        //skip space after move onto next one
        cmd = skipspace(next + 1);
        next = strchr(cmd, ' ');
    }

    //if the command is '\0\ then move into the next line
    if (cmd[0] != '\0') {
        args[i] = cmd;
        next = strchr(cmd, '\n');
        next[0] = '\0';
        ++i;
    }

    //set it to null
    args[i] = NULL;
}

//function for wait for process
static void waiting(int n)
{
    int i;
    for (i = 0; i < n; ++i)
        wait(NULL);
}
