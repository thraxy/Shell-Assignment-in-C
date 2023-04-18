// Mohammed Nabil Akbar
// Assignment 3 - Shell Upgrade
// Professor Dehzanghi
// Due: 04/08/2023

# include <stdio.h>
# include <stdlib.h>   // used to execute subprocess and commands
# include <string.h>
# include <unistd.h>   // used for exit, getcwd,read, write, exec
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h> // for ls
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>  // used for open

// read command line for the input line in shell
char *read_line(void)
{
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}

// parse the input command
char **parse(char *my_line)
{
    char **args = malloc(64 * sizeof(char*));
    char *arg;
    int i = 0;

    if (args == NULL) {
        fprintf(stderr, "\033[1;31mMemory allocation error\n\033[0m");
        exit(EXIT_FAILURE);
    }

    arg = strtok(my_line, " \t\r\n\a");
    while (arg != NULL) {
        args[i] = arg;
        i++;
        arg = strtok(NULL, " \t\r\n\a");
    }
    args[i] = NULL;
    return args;
}

// help command
void help_command() {
    printf("\033[1;35m\nList of available commands:\n\033[0m");
    printf("\033[1;33mhelp : Using this command will output the list of available commands.\n\033[0m");
    printf("\033[1;33mcd : Using this command, you can change the current working directory.\n\033[0m");
    printf("\033[1;33mpwd: Using this command will display the current working directory.\n\033[0m");
    printf("\033[1;33mls: Using this command will display the contents of current directory\n\033[0m");
    printf("\033[1;33mmkdir : Using this command will create a folder within directory.\n\033[0m");
    printf("\033[1;33mrmdir : Using this command will remove a folder within directory.\n\033[0m");
    printf("\033[1;33mcat : Using this command will display the contents of a file.\n\033[0m");
    printf("\033[1;33mgrep : Using this command will search for a pattern in a file.\n\033[0m");
    printf("\033[1;33mtouch : Using this command will create a file.\n\033[0m");
}

// cd command
void cd_command(char **args) {
    if (args[1] == NULL) {
        // prints only if there are no arguments
        fprintf(stderr, "cd: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }
}

// ls command
void ls_command() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        // prints the contents of the directory
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
}

// pwd command
void pwd_command() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // prints the current working directory
        printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
    }
}

// mkdir command
void mkdir_command(char **args) {
    if (args[1] == NULL) {
        // prints only if the argument is empty, returns error
        fprintf(stderr, "mkdir: expected argument to \"mkdir\"\n");
    } else {
        if (mkdir(args[1], 0777) == -1) {
            // creates the directory
            perror("mkdir");
        }
    }
}

// rmdir command
void rmdir_command(char **args) {
    if (args[1] == NULL) {
        // prints only if the argument is empty
        fprintf(stderr, "rmdir: expected argument to \"rmdir\"\n");
    } else {
        if (rmdir(args[1]) == -1) {
            // removes the directory
            perror("rmdir");
        }
    }
}

// cat command
void cat(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // prints only if the file is not found
        // \033[31m is the color code for red
        printf("\033[1;31mError: File not found\n\033[0m");
        return;
    }

    char line[1024];
    // while loop to read the file line by line
    // \x1b[42m green background color
    printf("\033[32mSuccess!\n\033[0m ");
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    // close the file
    fclose(file);
}

// touch command
void touch(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        // prints only if the file is not found
        // \033[31m is the color code for red
        // \033[0m is the color code for white
        printf("\033[1;31mError: File not found\n\033[0m");
        return;
    }
    printf("\033[1;32mSuccess!\n\033[0m");
    // close the file
    fclose(file);
}

// grep command
void grep(char *searchTerm, char *filename) {
    FILE *file = fopen(filename, "r");
    int lineCnt = 0;
    int patternCnt = 0;
    char *nextLine;

    if (file == NULL) {
        // prints only if the file is not found
        // \033[31m is the color code for red
        // \033[0m is the color code for white
        printf("\033[1;31mError: File not found\n\033[0m");
        return;
    }

    char line[1024];
    // while loop to read the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        lineCnt++;
        if (nextLine = strchr(line, '\n'))
            *nextLine = '\n';
        if (strstr(line, searchTerm) != NULL) {
            // prints the line if the search term is found
            printf("\033[1;42mSuccess!\n\033[0m");
            printf("\033[1;32m'%s' was found on line #%d:\033[0m %s\n", searchTerm, lineCnt, line);
            patternCnt++;
        }
    }

    // prints the pattern count
    printf("\n\033[1;32mThere is a pattern on %d lines\n\033[0m", patternCnt);
    // close the file
    fclose(file);
}

// main function
int main(int argc, char** argv)
{
    char *line;
    char **args;
    int status;

    // prints the welcome message
    printf("\033[1;36mWelcome to the Nabil's Shell! RUID: 176002999 \n\033[0m");
    printf("\033[1;33mPlease type the commands in the shell \n\033[0m");
    printf("\033[1;31mTo exit the shell, please type exit \n\033[0m");
    printf("\033[1;34mTo list the supported commands, please type help \n\033[0m");

    help_command(); // output the list of commands
    while (1) {
                    printf("\033[1;35m>> \033[0m");
        line = read_line();
        args = parse(line);
        // checks if the input command is in the list
        if (strcmp(args[0], "help") == 0) {
            help_command();
        } else if (strcmp(args[0], "cd") == 0) {
            cd_command(args);
        } else if (strcmp(args[0], "ls") == 0) {
            ls_command();
        } else if (strcmp(args[0], "pwd") == 0) {
            pwd_command();
        } else if (strcmp(args[0], "mkdir") == 0) {
            mkdir_command(args);
        } else if (strcmp(args[0], "rmdir") == 0) {
            rmdir_command(args);
        } else if (strcmp(args[0], "cat") == 0) {
            cat(args[1]);
        } else if (strcmp(args[0], "touch") == 0) {
            touch(args[1]);
        } else if (strcmp(args[0], "grep") == 0) {
            grep(args[1], args[2]);
        } else if (strcmp(args[0], "exit") == 0) {
            exit(EXIT_SUCCESS);
        } else {
            // prints only if the input command is not in the list
            printf("Command not recognized.\n");
        }
        free(line);
        free(args);
    }
    return 0;
}

