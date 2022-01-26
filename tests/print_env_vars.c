#include <stdio.h>
#include "../libft/libft.h"

int	main(int argc, char *argv[], char * envp[])
{
	int	i;

	(void)argc;
	(void)argv;
	for (i = 0; envp[i] != NULL; i++)
	{
    		//if (!ft_strncmp("SHELL", envp[i], 5))
			printf("%s\n", envp[i]);
	}
}

