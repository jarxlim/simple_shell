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
 * @ifn: argumnets
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
 * @ifn: struct address
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
		if (ifn->hist)
			free_list(&(ifn->hist));
		if (ifn->_alias)
			free_list(&(ifn->_alias));
		freef(ifn->environ);
			ifn->environ = NULL;
		bfree((void **)ifn->buffer_cmd);
		if (ifn->file_reader > 2)
			close(ifn->file_reader);
		_putchar(BUFFER_FLUSH);
	}
}
