#include "shell.h"
/**
 * find_history -find the history of files
 * @ents: structure of param
 * Return: pointer to string with history
 */
char *find_history(set_t *ents)
{
	char *buff, *directory;

	directory = _getenv(ents, "HOME=");
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
 * print_hist - make the new file or append to an existing one
 * @ents: parameters
 * Return: 1 on success, -1 when fails
 */
int print_hist(set_t *ents)
{
	ssize_t fds;
	char *fname = find_history(ents);
	list_t *nodes = NULL;

	if (!fname)
		return (-1);

	fds = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fds == -1)
		return (-1);
	for (nodes = ents->hist; nodes; nodes = nodes->next)
	{
		_printsf(nodes->str, fds);
		_pchar('\n', fds);
	}
	_pchar(BUFFER_FLUSH, fds);
	close(fds);
	return (1);
}
/**
 * hist_read - reads history from file
 * @ents: parameters
 * Return: number of hist count
 */
int hist_read(set_t *ents)
{
	int lncount = 0, a, end = 0;
	ssize_t filesize = 0, rdlength, fds;
	struct stat str;
	char *buff = NULL, *filename = find_history(ents);

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
	buff = malloc(sizeof(char) * (filesize + 1));
	if (!buff)
		return (0);
	rdlength = read(fds, buff, filesize);
	buff[filesize] = 0;
	if (rdlength <= 0)
		return (free(buff), 0);
	close(fds);
	for (a = 0; a < filesize; a++)
	{
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			append_list(ents, buff + end, lncount++);
			end = a + 1;
		}
	}
	if (end != a)
		append_list(ents, buff + end, lncount++);
	free(buff);
	ents->hist_size = lncount;
	while (ents->hist_size-- >= H_MAXIMUM)
		detach_node(&(ents->hist), 0);
	hist_recount(ents);
	return (ents->hist_size);
}

/**
 * append_list - adds to a linked list
 * @ents: param contains the argumens
 * @size: size of lines
 * @buffer: buffer pointing to the history
 * Return: 0 if success
 */
int append_list(set_t *ents, char *buffer, int size)
{
	list_t *point = NULL;

	if (ents->hist)
	{
		point = ents->hist;
	}
	append_node(&point, buffer, size);

	if (!ents->hist)
	{
		ents->hist = point;
	}
	return (0);
}

/**
 * hist_recount - renumbers the history
 * @ents: contains arguments
 * Return: new size
 */
int hist_recount(set_t *ents)
{
	list_t *point = ents->hist;
	int a = 0;

	while (point)
	{
		point->numbers = a++;
		point = point->next;
	}
	return (ents->hist_size = a);
}
