#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main() {
    printf("Hello World\n");

    // Write using System Call
    write(STDOUT_FILENO, "Hello World\n", sizeof("Hello World\n"));
    write(STDOUT_FILENO, "Hello World\n", strlen("Hello World\n"));

    return 0;
}

/*
    The program prints a string hello world to the console.
    Schematics:
        - The application runs in the userspace mode.
        - The header libraries are running in userspace mode.
        - printf function is defined in the library which internally
          makes a system call for write.

    To check system calls used by your program:
    use below command,
        strace a.out

        output: 

        write(1, "Hello World\n", 12Hello World)           = 12

        Find manual of Write using,
        man 2  write

        To see what header files are being used by program,
        use below command,
         gcc  -H <filename>.c

         Go to directory of header file and hit,
         grep "#define" unistd.h
*/