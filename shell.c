#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_LINE 1024
// read command line for the input line in shell

int parse_line(char *line, char** args){
    int count = 0;
    args[count] = strtok(line, " ");
    while (args[count] != NULL){
        count++;
        args[count] = strtok(NULL, " ");
    }
    return count;
}

int main(void){
    char line[MAX_LINE];

    while (1){
        printf(">> ");
        fgets(line, MAX_LINE, stdin);
        line[strlen(line) - 1] = '\0';
        if (strlen(line) == 0){
            continue;
        }

        char* args[MAX_LINE];
        int count = parse_line(line, args);

        if (strcmp(args[0], "cd") == 0){
            if (count < 2){
                printf("cd: missing operand \n");
                continue;
            }
            if (SetCurrentDirectory(args[1]) == 0){
                printf("cd: %s: No such file or directory \n", args[1]);
            }
        } else if (strcmp(args[0], "ls") == 0){
            system("dir");
        } else if (strcmp(args[0], "pwd") == 0){
            char cwd[MAX_LINE];
            if (GetCurrentDirectory(MAX_LINE, cwd) == 0){
                printf("pwd: cannot access current directory \n");
            } else {
                printf("%s \n", cwd);
            }
        } else if (strcmp(args[0], "mkdir") == 0){
            if (count < 2){
                printf("mkdir: missing operand \n");
                continue;
            }
            if (CreateDirectory(args[1], NULL) == 0){
                printf("mkdir: cannot create directory '%s': File exists \n", args[1]);
            }
        } else if (strcmp(args[0], "rmdir") == 0){
            if (count < 2){
                printf("rmdir: missing operand \n");
                continue;
            }
            if (RemoveDirectory(args[1]) == 0){
                printf("rmdir: failed to remove '%s': No such file or directory \n", args[1]);
            }
        } else if (strcmp(args[0], "help") == 0){
            printf("Shell Supported Commands: \n");
            printf("cd [directory] : change current working directory \n");
            printf("ls : displays current directory's contents \n");
            printf("pwd : displays current working directory \n");
            printf("mkdir [directory] : create a folder within a directory \n");
            printf("rmdir [directory] : remove a folder within a directory \n");
            printf("exit : exit the shell \n");
            printf("help : lists supported commands \n");
        } else if (strcmp(args[0], "exit") == 0){
            break;
        } else {
            printf("Command not found \n");
        }    
    } 
    return 0;
}