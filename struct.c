#include "shell.h"

/**
 * _format - initializes info_t structure
 * @ifn: adress for arguementss
 */
void _format(info_t *ifn)
{
	ifn->path = NULL;
        ifn->argc = 0;
	ifn->arv = NULL;
	ifn->argv = NULL;
}
/**
 * _initiate - initializes structure
 * @info: argumnets
 * @avt: argument array
 */
void _initiate(info_t *ifn, char **avt)
{
	int a = 0;

	ifn->file_name = avt[0];
	if (ifn->arv)
	{
		ifn->argv = strtow(ifn->arv, " \t");
		if (!ifn->argv)
		{

			ifn->argv = malloc(sizeof(char *) * 2);
			if (ifn->argv)
			{
				ifn->argv[0] = _strdup(ifn->arv);
				ifn->argv[1] = NULL;
			}
		}
		for (a = 0; ifn->argv && ifn->argv[a]; a++)
			;
		ifn->argc = a;

		change_alias(ifn);
		change_v(ifn);
	}
}
/**
 * free_info - function to free struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info(info_t *ifn, int all)
{
	freef(ifn->argv);
	ifn->argv = NULL;
	ifn->path = NULL;
	if (all)
	{
		if (!ifn->buffer_cmd)
			free(ifn->arv);
		if (ifn->envp)
			free_list(&(ifn->envp));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
