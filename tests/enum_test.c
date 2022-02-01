#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

typedef uint_fast8_t	t_access;

typedef enum	s_fflags
{
	F_EXISTS	= 0x01,
	F_CANREAD	= 0x02,
	F_CANWRITE	= 0x04,
	F_CANEXEC	= 0x08
}	t_fflags;

int	main(void)
{
	char	*filepath1 = "../files/colors.txt";
	char	*filepath2 = "../files/colors_000.txt";
	t_access	acc_stat;
	static t_fflags	file_flags;

	(void) filepath1;
	(void) filepath2;
	(void) acc_stat;
	printf("t_fflags file_flags = %lu\n", sizeof(t_fflags));
	printf("!access(filepath1, F_OK)) = %d\n", !access(filepath1, F_OK));
	printf("!access(filepath2, F_OK)) = %d\n", !access(filepath2, F_OK));
	printf("file_flags + 1 == %d\n", file_flags + 1);
	printf("file_flags + 2 == %d\n", file_flags + 2);
	printf("file_flags + 3 == %d\n", file_flags + 3);
	//So after a bit of digging, I realize now that what I was trying to achieve is impossible
	//An enum in c is nothing more than a way to enumerate a bunch of constants
}
