#include "ft_ls.h"

void		exit_unknown_option_error(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ft_ls [-alrRt] [file ...]\n", 2);
	exit(EXIT_FAILURE);
}

void		error_message(char *name, char *error_msg_prefix, t_bool close)
{
	ft_putstr_fd(name, 2);
	perror(error_msg_prefix);
	if (close)
		exit(EXIT_FAILURE);
}
