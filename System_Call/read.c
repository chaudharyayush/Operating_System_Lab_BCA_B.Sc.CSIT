// To read data from the standard input device and write it on the screen
#include <unistd.h>
int main()
{
    char buff[20];
    read(0, buff, 10);  // 0 is the file descriptor for standard input (keyboard), read 10 bytes from standard input device(keyboard), store in buffer (buff)
    write(1, buff, 10); // 1 is the file descriptor for standard output (screen), print 10 bytes from the buffer on the screen
}

// int n;
// char buff[30];
// n=read(0,buff,20);
// write(1,buff,n);