#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	int	pipe_fds[2];

	for (int i = 0; i < 5; i++)
	{
		pipe(pipe_fds);
		printf("pipe_fds[0] = %d\n", pipe_fds[0]);
		printf("pipe_fds[1] = %d\n", pipe_fds[1]);
	}
	return (0);
}
