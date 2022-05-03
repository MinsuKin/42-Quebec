#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

int main(int argc, char **argv)
{
    char *filename;
    int readn;
    char buf[80];

    while((readn = read(STDIN, buf, 80)) > 5)
    {
        // 읽어들인 데이터의 크기 만큼을 화면에 출력한다.
        write(STDOUT, buf, readn);
    }
    return 1;
}