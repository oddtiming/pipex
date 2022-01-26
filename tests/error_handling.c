#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int	main(void)
{
	int	fd1, fd2;

	fd1 = open("test.c", O_RDONLY);
	fd2 = 10;
	fd2 = dup2(fd1, fd2);
	printf("fd1 = %d\nfd2 = %d\n", fd1, fd2);
	close(fd1);
	close(fd2);

	fd1 = open("test.c", O_RDONLY);
	fd2 = -1;
	fd2 = dup2(fd1, fd2);
	printf("errno = %d\n", errno);
	perror("This is a test perror() message");
	printf("strerror(errno) = %s\n", strerror(errno));
	printf("Test: the current shell is $SHELL\n");
	close(fd1);
	close(fd2);
	return (0);
}
