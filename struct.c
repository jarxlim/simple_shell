#include "shell.h"

/**
 * _format - initializes set_t structure
 * @ents: adress for arguementss
 */
void _format(set_t *ents)
{
	ents->path = NULL;
	ents->argc = 0;
	ents->arv = NULL;
	ents->argv = NULL;
}
/**
 * _initiate - initializes structure
 * @ents: argumnets
 * @avt: argument array
 */
void _initiate(set_t *ents, char **avt)
{
	int a = 0;

	ents->file_name = avt[0];
	if (ents->arv)
	{
		ents->argv = strtow(ents->arv, " \t");
		if (!ents->argv)
		{

			ents->argv = malloc(sizeof(char *) * 2);
			if (ents->argv)
			{
				ents->argv[0] = _strdup(ents->arv);
				ents->argv[1] = NULL;
			}
		}
		for (a = 0; ents->argv && ents->argv[a]; a++)
			;
		ents->argc = a;

		change_alias(ents);
		change_v(ents);
	}
}
/**
 * free_info - free struct fields
 * @ents: struct address
 * @all: true if freeing all fields
 */
void free_info(set_t *ents, int all)
{
	freef(ents->argv);
	ents->argv = NULL;
	ents->path = NULL;
	if (all)
	{
		if (!ents->buffer_cmd)
		{
			free(ents->arv);
		}
		if (ents->envp)
		{
			free_list(&(ents->envp));
		}
		if (ents->hist)
		{
			free_list(&(ents->hist));
		}
		if (ents->_alias)
		{
			free_list(&(ents->_alias));
		}
		freef(ents->environ);
		{
			ents->environ = NULL;
		}
		bfree((void **)ents->buffer_cmd);
		if (ents->file_reader > 2)
		{
			close(ents->file_reader);
		}
		_putchar(BUFFER_FLUSH);
	}
}
