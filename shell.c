#include <stdio.h>
#include "shell.h"

/**
 * main - entry point for simple shell
 * @argc: argument counter
 * @argv: argument vector
 * @argp: env variables
 * Return: always 0
 */


int main(int argc, char **argv, char **argp)
{
	char *cmd = NULL, **cmds = NULL;
	size_t cmdlen = 0;
	int mode = !isatty(0), i = 0, cmdnum = 1, inputs = 0, ret;
	alias *head = NULL;

	print_error(argv[0], &inputs, NULL);
	environ = _arrdup(argp);
	if (argc > 1)
	{
		ret = runscript(argv[1]);
		free_pp(environ);
		exit(ret);
	}
	signal(SIGINT, handlerc);
	while (1)
	{
		cmd = NULL, cmds = NULL, get_input(&cmd, &cmdlen, &cmds, 0);
		cmdnum = _arlen(cmds), i = 0;
		free(cmd);
		inputs++;
		while (i < cmdnum)
			ret = exec_cmd(cmds, i, &head), i += 1;
		if (cmdnum > 0)
			free_pp(cmds);
		if (mode)
		{
			free_pp(environ), freealias(head);
			return (ret);
		}
	}
	free_pp(environ), freealias(head);
	return (ret);
}


