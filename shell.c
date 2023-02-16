#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_LINE 1024
// read command line for the input line in shell

// parse the input command

int parse_line(char *line, char** args){
    int count = 0;
    args[count] = strtok(line, " ");
    while (args[count] != NULL){
        count++;
        args[count] = strtok(NULL, " ");
    }
    return count;
}

// main function
int main(void){
    char line[MAX_LINE];
    // print the welcome message
    printf("Welcome to the Nabil's Shell \n");
    printf("Please type the commands in the shell \n");
    printf("To exit the shell, please type exit \n");
    printf("To list the supported commands, please type help \n");
    // while loop to read the input line
    while (1){        
        printf(">> ");
        // read the input line
        fgets(line, MAX_LINE, stdin);
        // remove the newline character
        line[strlen(line) - 1] = '\0';
        // check if the line is empty
        if (strlen(line) == 0){
            // if empty, continue to the next iteration
            continue;
        }
        
        char* args[MAX_LINE];
        // count parsed arguments 
        int count = parse_line(line, args);

        // check if the first argument is cd
        if (strcmp(args[0], "cd") == 0){
            // check if the second argument is empty
            if (count < 2){
                printf("cd: missing operand \n");
                continue;
            }
            // check if the directory exists
            if (SetCurrentDirectory(args[1]) == 0){
                // if not, print error message
                printf("cd: %s: No such file or directory \n", args[1]);
            }
            // if exists check if the directory is a file
        } else if (strcmp(args[0], "ls") == 0){
            // system passes the command to the command line
            system("dir");
            // check if the first argument is pwd
        } else if (strcmp(args[0], "pwd") == 0){
            char cwd[MAX_LINE];
            // get the current working directory
            if (GetCurrentDirectory(MAX_LINE, cwd) == 0){
                // if not, print error message
                printf("pwd: cannot access current directory \n");
            } else {
                // if exists, print the current working directory
                printf("%s \n", cwd);
            }
            // check if the first argument is mkdir
        } else if (strcmp(args[0], "mkdir") == 0){
            // check if the second argument is empty
            if (count < 2){
                printf("mkdir: missing operand \n");
                continue;
            }
            // check if the directory exists
            if (CreateDirectory(args[1], NULL) == 0){
                // if not, print error message
                printf("mkdir: cannot create directory '%s': File exists \n", args[1]);
            }
            // check if the first argument is rmdir
        } else if (strcmp(args[0], "rmdir") == 0){
            // check if the second argument is empty
            if (count < 2){
                // if empty, print error message
                printf("rmdir: missing operand \n");
                continue;
            }
            // check if the directory exists
            if (RemoveDirectory(args[1]) == 0){
                // if not, print error message
                printf("rmdir: failed to remove '%s': No such file or directory \n", args[1]);
            }
            // check if the first argument is help
        } else if (strcmp(args[0], "help") == 0){
            // print the supported commands
            printf("Shell Supported Commands: \n");
            printf("cd [directory] : change current working directory \n");
            printf("ls : displays current directory's contents \n");
            printf("pwd : displays current working directory \n");
            printf("mkdir [directory] : create a folder within a directory \n");
            printf("rmdir [directory] : remove a folder within a directory \n");
            printf("exit : exit the shell \n");
            printf("help : lists supported commands \n");
            // check if the first argument is exit
        } else if (strcmp(args[0], "exit") == 0){
            // exit the shell
            break;
        } else {
            // if the command is not supported, print error message
            printf("Command not found \n");
        }    
    } 
    // exit the shell
    return 0;
}