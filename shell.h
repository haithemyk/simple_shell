#ifndef SHELL_H_INCLUDED
#define SHELL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * For Write/Read Buffers
 */
#define WRITE_BUF_SIZE		1024
#define READ_BUF_SIZE		1024
#define BUF_FLUSH		-1
=======
#define WRITE_BUF_SIZE		1024
#define READ_BUF_SIZE		1024
#define BUF_FLUSH		-1

/*
 * For Command Chaining
 */
#define CMD_NORM		0
#define CMD_OR			1
#define CMD_AND			2
#define CMD_CHAIN		3
=======
#define CMD_NORM		0
#define CMD_OR			1
#define CMD_AND			2
#define CMD_CHAIN		3

/*
 * For convert_number()
 */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*
 * 1. If Using system getline()
 */
#define USE_GETLINE		0
#define USE_STRTOK		0

#define HIST_FILE		".simple_shell_history"
#define HIST_MAX		4096
=======
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE		".simple_shell_history"
#define HIST_MAX		4096

extern char **environ;

/**
 * struct liststr - for singly linked list
 * @num: pointer to the number field
 * @str: pointer to a string
 * @next: pointer to the next Node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - consists of pseudo-arguments to pass into
 * a function, permitting a uniform prototype for the function
 * pointer struct.
 * @arg: points to a string generated from getline containing arguments
 * @argv: pointer to an array of strings generated from arg
 * @path: pointer to a string path for the current command
 * @argc: argument count pointer
 * @line_count: error count pointer
 * @err_num: error code for exit()s pointer
 * @linecount_flag: line of input on count
 * @fname: the program filename pointer
 * @env: linked list local copy of environ pointer
 * @environ: points to custom modified copy of environ from LL env
 * @history: the history node pointer
 * @alias: the alias node pointer
 * @env_changed: ON if environ was changed pointer
 * @status: points to return status of the last exec'd command
 * @cmd_buf: points to address of pointer to cmd_buf, ON if chaining
 * @cmd_buf_type: points to CMD_type ||, &&, ;
 * @readfd: fd from which to read line input pointer
 * @histcount: pointer to the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* points to cmd ; chain buffer, memory management */
	int cmd_buf_type; /* points to CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - consists of a builtin string
 * and a related function.
 * @type: builtin command flag pointer
 * @func: function pointer
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/*
 * For getline.c
 */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*
 * For atoi.c
 */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/*
 * For builtin1.c
 */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/*
 * For builtin2.c
 */
int _myhistory(info_t *);
int _myalias(info_t *);

/*
 * For error_output1.c
 */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/*
 * For error_output2.c
 */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*
 * For environment.c
 */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);

/*
 * For exit.c
 */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

#endif
