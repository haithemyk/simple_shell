#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>
int execute(char** argv)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (-1);
	}
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			return(-1);
		}
	}
	else
	{
        wait(&status);
	return (0);
	}
	return (0);
	
	
}
