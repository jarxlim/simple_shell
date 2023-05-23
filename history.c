#include "shell.h"
/**
 * find_history -find the history of files
 * @ifn: structure of param
 * Return: pointer to string with history
 */
char *find_history(info_t *ifn)
{
	char *buff, *directory;

	directory = _getenv(ifn, "HOME=");
	if (!directory)
	{
		return (NULL);
	}
	buff = malloc(sizeof(char) * (_strlen(directory) + _strlen(FILE_HIST) + 2));

	if (!buff)
	{
		return (NULL);
	}
	buff[0] = 0;
	_strcpy(buff, directory);
	_strcat(buff, "/");
	_strcat(buff, FILE_HIST);
	return (buff);
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
 * hist_read -reads history from file
 * @ifn: structure info for parameters
 * Return: number of hist count 
 */
int hist_read(info_t *ifn)
{
	int lncount = 0, a, end = 0;
	ssize_t filesize = 0, rdlength, fds;
	struct stat str;
	char *buff = NULL, *filename = find_history(ifn);

	if (!filename)
	{
		return (0);
	}
	fds = open(filename, O_RDONLY);
	free(filename);
	if (fds == -1)
	{
		return (0);
	}
	if (!fstat(fds, &str))
	{
		filesize = str.st_size;
	}
	if (filesize < 2)
	{
		return (0);
	}
	buff = malloc(sizeof(char) * (filesize + 1));
	if (!buff)
	{
		return (0);
	}
	rdlength = read(fds, buff, filesize);
	buff[filesize] = 0;
	if (rdlength <= 0)
	{
		return (free(buff), 0);
	}
	close(fds);
	for (a = 0; a < filesize; a++)
	{
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			append_list(ifn, buff + end, lncount++);
			end = a + 1;
		}
	}
	if (end != a)
	{
		append_list(ifn, buff + end, lncount++);
	}
	free(buff);
	ifn->hist_size = lncount;
	while (ifn->hist_size-- >= H_MAXIMUM)
	{
		detach_node(&(ifn->hist), 0);
	}
	hist_recount(ifn);
	return (ifn->hist_size);
}

/**
 * append_list - adds to a linked list
 * @ifn: contains the argumens
 * @size: size of lines 
 * @buffer: buffer pointing to the history
 * Return: 0 if success
 */
int append_list(info_t *ifn, char *buffer, int size)
{
	list_t *point = NULL;

	if (ifn->hist)
	{
		point = ifn->hist;
	}
	append_node(&point, buffer, size);

	if (!ifn->his)
	{
		ifn->hist = point;
	}
	return (0);
}

/**
 * hist_recount - renumbers the history
 * @ifn: contains arguments
 * Return: new size 
 */
int hist_recount(info_t *ifn)
{
	list_t *point = ifn->hist;
	int a = 0;

	while (point)
	{
		point->numbers = a++;
		point = point->next;
	}
	return (ifn->hist_size = a);
}
