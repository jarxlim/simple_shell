#include "main.h"
/**
 * get_history_file -function to get the history of files
 * @info: structure of parameter
 * Return: pointer to string with history
 */
char *get_history_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history -function to make the new file or append to an existing one
 * @info: the structure of pparameters
 * Return: 1 for success, -1 for failure
 */
int write_history(info_t *info)
{
	ssize_t fds;
	char *fname = get_history_file(info);
	list_t *nodes = NULL;

	if (!fname)
		return (-1);

	fds = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fds == -1)
		return (-1);
	for (nodes = info->history; nodes; nodes = nodes->next)
	{
		_putsfd(nodes->str, fds);
		_putfd('\n', fds);
	}
	_putfd(BUF_FLUSH, fds);
	close(fds);
	return (1);
}

/**
 * read_history -function to read history from file
 * @info: the dtructure info for parameters
 * Return: number of hist counted returned for success or 0 otherwise
 */
int read_history(info_t *info)
{
	int lncount = 0, a, end = 0;
	ssize_t filesize = 0, rdlength, fds;
	struct stat str;
	char *buffer = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fds = open(filename, O_RDONLY);
	free(filename);
	if (fds == -1)
		return (0);
	if (!fstat(fds, &str))
		filesize = str.st_size;
	if (filesize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (filesize + 1));
	if (!buffer)
		return (0);
	rdlength = read(fds, buffer, filesize);
	buffer[filesize] = 0;
	if (rdlength <= 0)
		return (free(buffer), 0);
	close(fds);
	for (a = 0; a < filesize; a++)
		if (buffer[a] == '\n')
		{
			buffer[a] = 0;
			build_history_list(info, buffer + end, lncount++);
			end = a + 1;
		}
	if (end != a)
		build_history_list(info, buffer + end, lncount++);
	free(buffer);
	info->histcount = lncount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure innnfo that contains the argumens
 * @linecount: number of lines conted
 * @buf: the buffer for pointing to the hist
 * Return: 0 as success
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *point = NULL;

	if (info->history)
		point = info->history;
	add_node_end(&point, buf, linecount);

	if (!info->history)
		info->history = point;
	return (0);
}

/**
 * renumber_history - function that can recount the hist
 * @info: Structure info that contains arguments
 * Return: new number of coounts
 */
int renumber_history(info_t *info)
{
	list_t *point = info->history;
	int a = 0;

	while (point)
	{
		point->num = a++;
		point = point->next;
	}
	return (info->histcount = a);
}
