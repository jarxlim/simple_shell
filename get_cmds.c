#include "main.h"

/**
 * is_cmd - funtion to check if a file is an executable command
 * @info: the info struct that contain argus
 * @path: path to the file to be checked
 * Return: 1 for true, 0 for false
 */
int is_cmd(info_t *info, char *path)
{
	struct stat str;

	(void)info;
	if (!path || stat(path, &str))
		return (0);

	if (str.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function to duplicate characters
 * @pathstr: the PATH string to check in
 * @start: starting point
 * @stop: stopping point
 *
 * Return: pointer to the new string
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int a = 0, p = 0;

	for (p = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buffer[p++] = pathstr[a];
	buffer[p] = 0;
	return (buffer);
}

/**
 * find_path - function to find cmand in the PATH string
 * @info: the info struct for arguments
 * @pathstr: the PATH string to search
 * @cmd: the input command for checking
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, current_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = dup_chars(pathstr, current_pos, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[a])
				break;
			current_pos = a;
		}
		a++;
	}
	return (NULL);
}
