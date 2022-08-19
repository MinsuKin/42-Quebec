#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd)
{
    char *s = malloc(10000);
    char *c = s;

    while (read(fd, c, 1) > 0 && *c++ != '\n');
    return c > s ? (*c = 0, s) : (free(s), NULL);
}