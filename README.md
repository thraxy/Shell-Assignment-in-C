# **Shell-Assignment-in-C**

For my Operating Systems class our first assignment was to create my own shell in C.

### **Required Commands**

* help
    > This command will output the list of available commands for the shell.
* cd
    > Using this command, you can change the current working directory.
* ls
    > Using this command will display the contents of current directory.
* pwd
    > Using this command will display the current working directory
* mkdir
    > This command will be used to create a folder within the directory. It should give an error if argument to this command is empty.
* rmdir
    > This command will be used to remove a folder within the directory. It should give an erro if there is an empty argument to this command or if the directory does not exist.

#### **Notes**

The current program works for me currently because I am using a windows machine. I imported:

``` #include <windows.h> ```

I had to do the implementation for this assignment this way because I was running into issues using the given header files, which seem to work for linux. Those header files include:

``` #include <unistd.h> ```  ``` #include <sys/wait.h> ``` 
``` #include <sys/types.h> ``` ``` #include <dirent.h> ```

``` #include <errno.h> ``` ``` #include <sys/stat.h> ```
``` #include <fcntl.h> ```

Since I wasted a lot time going back and forth and spending time reading the documentation on the header files that were given to me to use. I decided not to use them for now just so I can have something functional to work with.

Currently now until the assignment is due the goal is to use and implement the given header files and have the shell work on a linux distribution.

