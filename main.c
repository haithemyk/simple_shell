#include "main.h"
/**
 * main - the entry of the shell.
 * Return: 0 if the success of the program.
*/
int main(void)
{
	char* command;
	size_t buffer_size;
	size_t characters;
	char **argv;
	while (1)
	{
		printf("$ ");
		fflush(stdout);
		characters = getline(&command, &buffer_size, stdin);
		if ((int) characters == EOF)
		{
			puts("");
			break;
		}
		argv = command_spliter(command);
		if (characters != 0)
		{
			if(execute(argv) == 1)
				printf("command not found:%s\n", command);
		}
		printf("command is: %s\n", command);
		printf("characters is: %ld\n", characters);
		
		
	}
	free(command);
	return (0);

}
