#include <unistd.h>
#include <stdio.h>

execve(cmd)
exit(1);

extern char **environ;

int main(int argc, char *argv[], char *envp[])
{
    char *exec_argv[] = { "/bin/bash", "-c", "cd tests", 0 };
    char *exec_envp[] =
    {
        "HOME=/",
        "PATH=/bin:/usr/bin",
        "PWD=/Users/iyahoui-/poop"
        "USER=execve_test",
        "LOGNAME=execve_test_logname",
        0
    };

    execve(exec_argv[0], &exec_argv[0], environ);
    fprintf(stderr, "Oops!\n");
    return -1;
}
