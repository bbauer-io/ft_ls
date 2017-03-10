/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 11:09:34 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/09 22:04:13 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_printf("ft_ls: %s: %s", filename, strerror(errno));
		return (0);
	}
}

/*
** This functions compares the length of column and saves the largest so that
** the width can be easily formatted with printf.
** It also tests for S_IFBLK and S_IFCHR (block special and character special)
** which would indicate the the file is in face a device.
*/

void		calc_col_widths_get_dev_info(t_list *file_list, int *w)
{
	t_file		*tmp;

	ft_bzero(w, sizeof(int) * 7);
	while (file_list)
	{
		tmp = (t_file *)file_list->content;
		w[0] = MAX(ft_nbrlen(tmp->stats.st_nlink), w[0]);
		if (getpwuid(tmp->stats.st_uid))
			w[1] = MAX(ft_strlen(getpwuid(tmp->stats.st_uid)->pw_name), w[1]);
		else
			 w[1] = MAX(ft_strlen(ft_itoa(tmp->stats.st_uid)), w[1]);
		if (getgrgid(tmp->stats.st_gid))
			w[2] = MAX(ft_strlen(getgrgid(tmp->stats.st_gid)->gr_name), w[2]);
		else
			w[2] = MAX(ft_strlen(ft_itoa(tmp->stats.st_gid)), w[2]);
		w[3] = MAX(ft_nbrlen(tmp->stats.st_size), w[3]); // I think I can use this without nbrlen
		w[4] = MAX(ft_nbrlen(tmp->stats.st_rdev >> 24), w[4]);
		w[5] = MAX(ft_nbrlen(tmp->stats.st_rdev & 0xFFFFFF), w[5]);
		w[6] = (((tmp->stats.st_mode & S_IFMT) == S_IFBLK) ||
				((tmp->stats.st_mode & S_IFMT) == S_IFCHR) ? 1 : 0);
		file_list = file_list->next;
	}
	w[0]++;
}

/*
** If a bad option is found in the user input, the program calls this function
** to report the error and exit the program.
*/

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
