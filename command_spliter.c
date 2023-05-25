#include "main.h"
/**
 * command_spliter - split command into small tokens
 * @cmnd:the command passed by user
 * Return:the array of string
 */
char **command_spliter(char cmnd[])
{
	char *token;
	int num_token;
	int size;
	char **args;

	size = 10;
	token = strtok(cmnd, " ");
	num_token = 0;
	args = malloc(sizeof(char *) * size);
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
		args = realloc(args, size  * sizeof(char *));
	}
	handle_path(args);
	args[num_token] = NULL;
	free(token);
	return (args);
}
/**
 * handle_path - the path if exists or not
 * @args:arguments
 */
void handle_path(char **args)
{
	char *command;
	char *path;
	char *fullPath;
	int exists;

	command = args[0];
	path = "/bin/";
	if (strchr(command, '/') == NULL)
	{
		fullPath = malloc(strlen(path) + strlen(command) + 2);
		snprintf(fullPath,
				strlen(path) + strlen(command) + 2,
				"%s/%s", path, command);
		exists = access(fullPath, X_OK);
		if (exists == 0)
		{
			args[0] = strdup(fullPath);
			free(fullPath);
			return;
		}
		free(fullPath);
	}
}
