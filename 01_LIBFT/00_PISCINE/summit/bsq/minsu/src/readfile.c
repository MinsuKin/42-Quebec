# include <stdio.h> 
# include <fcntl.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# define BUF_SIZE 4096

int	main(int argc, char **argv)
{
	char buf[BUF_SIZE + 1];
	int	fd;
	int ret;

	if (argc == 1)
		return (0);
	fd = open(argv[1], O_RDONLY);
	ret = read(fd, buf, BUF_SIZE);
	buf[ret] = '\0';
	printf("%s\n", buf);
	if (close(fd) == -1)
		return (1);
	return (0);
}
