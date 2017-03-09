#include "../includes/ft_ls.h"

/*
** Returns (1) if lstat finds a valid file and can access it. Else it will print
** an error message and return (0);
*/

t_bool		file_is_accessible(char *filename)
{
	struct stat		stbuf;

	if (lstat(filename, &stbuf) == 0)
		return (1);
	else
	{
		ft_printf("ft_ls: %s", filename);
		perror("");
		return (0);
	}
}


