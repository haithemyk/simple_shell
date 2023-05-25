#include "main.h"
/**
 * main - the entry of the shell.
 * Return: 0 if the success of the program.
*/
int main(int ac, char **av, char **env)
{
	char *command;
	size_t buffer_size;
	size_t characters;
	char **argv;
	unsigned int i = 0;
	while (1)
	{
		printf("%s",av[0]);
		printf("$ ");
		fflush(stdout);
		characters = getline(&command, &buffer_size, stdin);
		if ((int) characters == EOF)
		{
			puts("");
			break;
		}
		argv = command_spliter(command);
		if (strcmp(argv[1], "exit") == 0)
			exit(0);
		if (strcmp(argv[1], "env") == 0)
		{
			i = 0;
			while (env[i] != NULL)
			{
				printf("%s\n", env[i++]);
			}
		}
		if (characters != 0)
		{
			if (execute(argv) == 1)
				printf("%s:No such file or directory\n",av[ac - 1]);
		}
	}
	free(command);
	free(argv);
	return (0);

}
