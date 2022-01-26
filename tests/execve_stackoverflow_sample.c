#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    char *exec_argv[] = { "/usr/bin/env", 0 };
    char *exec_envp[] =
    {
        "HOME=/",
        "PATH=/bin:/usr/bin",
        "PWD=/Users/iyahoui-/poop"
        "USER=execve_test",
        "LOGNAME=execve_test_logname",
        0
    };

    execve(exec_argv[0], &exec_argv[0], envp);
    fprintf(stderr, "Oops!\n");
    return -1;
}
