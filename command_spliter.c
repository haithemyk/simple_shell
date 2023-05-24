#include "main.h"
char** command_spliter(char cmnd[])
{
	char *token;
	int num_token;
	int size;
	char **args;

	size = 10;
	token = strtok(cmnd, " ");
	num_token = 0;
	args = malloc(sizeof(char*) * size);
	while (token != NULL)
	{
		token[strcspn(token, "\n")] = '\0';
		args[num_token] = token;
		token = strtok(NULL, " ");
		num_token++;
	}
	if (num_token == size)
	{
		size++;
		args = realloc(args, size  * sizeof(char*));
	}
	args[num_token] = NULL;
	return args;
}
