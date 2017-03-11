/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:26:23 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/10 17:25:26 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** <dirent.h>			opendir(), readdir(), closedir()
** <sys/stat.h>			stat(), lstat()
** <sys/types.h>		dev_t, ino_t (in stat struct)
** <string.h>			strerror()
** <errno.h>			access to errno global variable
** <sys/types.h>		getpwuid()
** <pwd.h>				getpwuid()
** <uuid/uuid.h>		getpwuid(), getgrgid()
** <grp.h>				getgrgid()
*/

# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>

# define SIX_MONTHS 15552000

typedef struct	s_opt
{
	t_bool		l;
	t_bool		up_r;
	t_bool		a;
	t_bool		r;
	t_bool		t;
}				t_opt;

typedef struct	s_file
{
	char			*name;
	struct stat		stats;
}				t_file;

t_bool			file_is_accessible(char *filename);
void			exit_unknown_option_error(char c);
void			error_message(char *name, char *error_msg_prefix, t_bool close);
void			process_arguments(t_list *file_list, t_opt *opts, int list_len);
void			calc_col_widths_get_dev_info(t_list *file_list,
															unsigned int *w);
void			explore_all_subdirectories(t_list *entries, t_list *file_list,
															t_opt *opts);
void			lst_sort(t_list *start, int (*f)(t_file *, t_file *, int),
															int reverse_order);
int				cmp_chrono(t_file *p1, t_file *p2, int reverse_order);
int				cmp_alpha(t_file *p1, t_file *p2, int reverse_order);
t_list			*open_directory(t_list *parent, t_list *file_list, t_opt *opts);
void			print_w_stats(t_file *file, t_file *parent, unsigned int *info);

#endif
