/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:10:33 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/07 17:53:48 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** Scans all arguments beginning with '-' for options a, l, r ,R, t and returns
** a struct with the saved results.
*/

static t_opt		*read_options(int ac, char **av)
{
	int			i;
	int			j;
	t_opt		*opts;

	opts = ft_memalloc(sizeof(t_opt));
	i = 1;
	while (i++ < ac)
	{
		j = 0;
		while (av[i][0] == '-' && av[i][j++] != '\0')
		{
			if (!ft_strchr("alrRt", av[i][j]))
				exit_unknown_option_error(av[i][j]);
			opts->a = (av[i][j] == 'a' ? 1 : opts->a);
			opts->l = (av[i][j] == 'l' ? 1 : opts->l);
			opts->r = (av[i][j] == 'r' ? 1 : opts->r);
			opts->up_r = (av[i][j] == 'R' ? 1 : opts->up_r);
			opts->t = (av[i][j] == 't' ? 1 : opts->t);
		}
	}
	return (opts);
}

static t_list		*create_valid_arg_list(int ac, char **av, int *good_args)
{
	int			i;
	t_list		*file_list;
	t_file		*tmp;

	i = 0;
	file_list = NULL;
	tmp = (t_file *)ft_memalloc(sizeof(t_file));
	while (++i < ac)
	{
		if (av[i][0] != '-' && !file_is_accessible(av[i]))
		{
			ft_printf("ft_ls: %s: ", av[i]);
			perror("");
		}
		else
		{
			tmp->name = ft_strdup(av[i]);
			lstat(tmp->name, &(tmp->stats));
			ft_lst_append(&file_list, ft_lstnew(tmp, sizeof(t_file)));
			(*good_args)++;
		}
	}
	free(tmp);
	return (file_list);
}

static t_list		*scan_dirs(int ac, char **av, t_opt *opts)
{
	t_list		*file_list;
	t_file		*tmp;
	int			good_args;

	good_args = 0;
	tmp = (t_file *)ft_memalloc(sizeof(t_file));
	file_list = create_valid_arg_list(ac, av, &good_args);
	if (good_args == 0 && !ft_lst_len(file_list))
	{
		tmp->name = ft_strdup(".");
		lstat(tmp->name, &(tmp->stats));
		ft_lst_append(&file_list, ft_lstnew(tmp, sizeof(t_file)));
	}
	else
		lst_sort(file_list, (opts->t ? &cmp_chrono : &cmp_alpha), opts->r);
	free(tmp);
	return (file_list);

}

int				main(int argc, char **argv)
{
	t_opt		*opts;
	t_list		*file_list;
	int			list_length;

	opts = read_options(argc, argv);
	file_list = scan_dirs(argc, argv, opts);
	list_length = ft_lst_len(file_list);

	print_list(file_list, opts, list_length);

	ft_lstdel(&file_list, &ft_lst_free_contents);
	free(opts);
	return (0);
}
