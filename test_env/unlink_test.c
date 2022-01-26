#include <unistd.h>

int main(int argc, char *argv[])
{
	int	status;

	status = access(argv[1], F_OK);
	unlink("result.txt");

	return 0;
}
