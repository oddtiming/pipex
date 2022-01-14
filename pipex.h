#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>

//TO REMOVE
# include <stdio.h>

typedef struct s_args
{
	int		argc;
	char	*in_file;
	char	*out_file;
	char	**cmd1;
	char	**cmd2;
	char	**pathv;
}

#endif