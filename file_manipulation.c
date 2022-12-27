#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main (int argc, char *argv[]) {

    int filedescriptor, filetoremove, filetowrite;
    char filecontent[100];
    size_t readbytes, writebytes;
    
    /**
     * Creating a file using open system call,
     * int open(const char *pathname, int flags, mode_t mode);
     * Flags --> RDWR and CREAT
     * Mode  -->  0755
     * Creates or open file for Read or write operation.
    */
    filedescriptor = open("newfile.txt", O_RDWR | O_CREAT, 0755);
    filetoremove = open("delete.txt", O_RDWR | O_CREAT, 0755);
    filetowrite = open("written.txt", O_RDWR | O_CREAT, 0755);
    

    if ( filedescriptor < 0 || filetoremove < 0 || filetowrite < 0) {
        printf("File can't be created/opened");
        exit(1);
    }

    /**
     * Reading file data using read system call,
     * ssize_t read(int fd, void *buf, size_t count);
     * 
    */
     readbytes = read(filedescriptor, filecontent, 100);
     if (readbytes < 0 ) {
        printf("File read failed");
        exit(1);
     }
     else {
        printf("The readcount is : %li\n",readbytes);
        printf("The data is : %s\n",filecontent);
     }
     while(readbytes > 0 ) {
        printf("%s\n",filecontent);
        readbytes = read(filedescriptor, filecontent, 100);
     }

    /**
     * Writing to a file using lseek system call,
     * off_t lseek(int fd, off_t offset, int whence);
     * whence --> SEEK_SET | SEEK_CUR | SEEK_END
    */
    char *writethis = "Writing to the file at the end"; 
    lseek(filedescriptor, 0, SEEK_END);
    if (lseek < 0 ) {
        printf("File lseek failed");
        exit(1);
    }
    else {
        if (write(filedescriptor, writethis, strlen(writethis))< 0) {
            printf("Write with LSEEK failed");
            exit(1);
        }
    }

    /**
     * Writing to a file using write system call,
     * ssize_t write(int fd, const void *buf, size_t count);
    */
    writebytes = write(filetowrite, filecontent, strlen(filecontent));
    if ( writebytes < 0 ) {
        printf(" File write failed");
        exit(1);
    }

    /**
     * Closing file using close system call,
     *  int close(int fd);
     * fd --> File descriptor for thr file that needs to be closed
    */
    if( close(filedescriptor) < 0 || close(filetoremove) < 0 || close(filetowrite) ) {
        printf("File close failed");
        exit(1);
    }

    /**
     * Removing file using remove system call,
     * int remove(const char *pathname);
    */
    if ( remove("delete.txt") < 0 ) {
        printf("File deletion failed");
        exit(1);
   }

    return 0;
}