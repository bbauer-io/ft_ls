/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 17:10:33 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/09 17:52:39 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** Scans all arguments beginning with '-' for options a, l, r ,R, t and returns
** a struct with the saved results. Specifying a bad option results in the
** program exiting.
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

/*
** Reads the arguments provided by the user, tests that they are valid files
** and/or directories, then adds each to a new list that it creates. The list
** contains the file or directory name, and the results of a call to lstat().
*/

static t_list		*populate_from_valid_args(int ac, char **av, int *good_args)
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
			ft_printf("ft_ls: %s: %s", av[i], strerror(errno));
			//(*good_args)++
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

/*
** Creates the list of files or directories to be listed from each argument.
** If no args are present, it creates a single list item for the current dir.
** The list is then sorted based on the flags that are set.
*/

static t_list		*scan_dirs(int argc, char **argv, t_opt *opts)
{
	t_list		*file_list;
	t_file		*tmp;
	int			good_args;

	good_args = 0;
	tmp = (t_file *)ft_memalloc(sizeof(t_file));
	file_list = populate_from_valid_args(argc, argv, &good_args);
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

/*
** ENTRY POINT OF FT_LS
*/

int				main(int argc, char **argv)
{
	t_opt		*opts;
	t_list		*file_list;
	int			list_length;

	opts = read_options(argc, argv);
	file_list = scan_dirs(argc, argv, opts);
	list_length = ft_lst_len(file_list);
	process_arguments(file_list, opts, list_length);
	ft_lstdel(&file_list, &ft_lst_free_contents);
	free(opts);
	return (0);
}
