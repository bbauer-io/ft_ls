/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 16:26:23 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/07 17:51:10 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>


typedef struct		s_opt
{
	t_bool			l;
	t_bool			up_r;
	t_bool			a;
	t_bool			r;
	t_bool			t;
}					t_opt;

typedef struct		s_file
{
	char			*name;
	struct stat		stats;
}					t_file;


t_bool		file_exists(char *filename);
void		exit_unknown_option_error(char c);
void		error_message(char *name, char *error_msg_prefix, t_bool close);

void		lst_sort(t_list *start, int (*f)(t_file *, t_file *, int),
															int reverse_order);
int			cmp_chrono(t_file *p1, t_file *p2, int reverse_order);
int			cmp_alpha(t_file *p1, t_file *p2, int reverse_order);

#endif
