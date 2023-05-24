#include "shell.h"

/**
 * check_cmd - funtion to check if a file is an executable command
 * @ifn: theibject of  pinfo struct that contain argus
 * @path: path to the file to be checked
 * Return: 1 for true, 0 for false
 */
int check_cmd(info_t *ifn, char *path)
{
	struct stat str;

	(void)ifn;
	if (!path || stat(path, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chars_dup - function to duplicate characters
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
 * path_finder - function to find cmand in the PATH string
 * @ifn: the oject of pinfo struct for arguments
 * @ptstr: the PATH string to search
 * @cmd: the input command for checking
 *
 * Return: full path of cmd if found or NULL
 */
char *path_finder(info_t *ifn, char *ptstr, char *cmd)
{
	int a = 0, current_pos = 0;
	char *path;

	if (!ptstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && _leet(cmd, "./"))
	{
		if (check_cmd(ifn, cmd))
			return (cmd);
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
			if (check_cmd(ifn, path))
				return (path);
			if (!ptstr[a])
				break;
			current_pos = a;
		}
		a++;
	}
	return (NULL);
}
