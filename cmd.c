#include "shell.h"

/**
 * check_cmd - check if a file is an executable command
 * @ents: param
 * @path: path to the file
 * Return: 1 f true, 0 if false
 */
int check_cmd(set_t *ents, char *path)
{
	struct stat str;

	(void)ents;
	if (!path || stat(path, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chars_dup - duplicate characters
 * @ptstr: the PATH string to check in
 * @start: starting point
 * @stop: stopping point
 *
 * Return: pointer to the new string
 */
char *chars_dup(char *ptstr, int start, int stop)
{
	static char buffer[1024];
	int a = 0, p = 0;

	for (p = 0, a = start; a < stop; a++)
	{
		if (ptstr[a] != ':')
			buffer[p++] = ptstr[a];
	}
	buffer[p] = 0;
	return (buffer);
}

/**
 * path_finder - find cmand in the PATH string
 * @ents: param
 * @ptstr: the PATH string to search
 * @cmd: command for checking
 * Return: path of cmd if found or NULL
 */
char *path_finder(set_t *ents, char *ptstr, char *cmd)
{
	int a = 0, current_pos = 0;
	char *path;

	if (!ptstr)
	{
		return (NULL);
	}
	if ((_strlen(cmd) > 2) && _leet(cmd, "./"))
	{
		if (check_cmd(ents, cmd))
		{
			return (cmd);
		}
	}
	while (1)
	{
		if (!ptstr[a] || ptstr[a] == ':')
		{
			path = chars_dup(ptstr, current_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (check_cmd(ents, path))
				return (path);
			if (!ptstr[a])
				break;
			current_pos = a;
		}
		a++;
	}
	return (NULL);
}
