/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 13:46:02 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/09 17:52:24 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void		print_blocks_total(t_list *file_list)
{
	blkcnt_t		total;
	struct stat		stbuf;

	total = 0;
	while (file_list)
	{
		total += ((t_file *)file_list->content)->stats.st_blocks;
		file_list = file_list->next;
	}
	stat("/", &stbuf);
	ft_printf("total %zu blocks (%ukb blocksize)\n", total, stbuf.st_blksize);
}

static void		print_dir_contents(t_list *parent, t_list *file_list,
																t_opt *opts)
{
	t_list		*entries;
	t_list		*tmp_entries;
	int			info[7];

	if (!(entries = open_dir(parent, file_list, opts)))
		return ;
	if (opts->l)
		print_blocks_total(entries);
	lst_sort(entries, (opts->t) ? cmp_chrono : cmp_alpha, opts->r);
	tmp_entries = entries;
	calc_col_widths_get_dev_info(entries, info);
	while (entries)
	{
		if (opts->l)
			print_w_stats((t_file *)entries->content,
							((t_file *)file_list->content), opts, info);
		else
			ft_printf("%s\n", ((t_file *)entries->content)->name);
		entries = entries->next;
		
	}
	entries = tmp_entries;
	if (opts->up_r)
		explore_subdirectories(entries, file_list, opts);
}

void			explore_subdirectories(t_list *entries, t_list *file_list,
																t_opt *opts)
{
	while (entries)
	{
		if (S_ISDIR(((t_file *)entries->content)->stats.st_mode) &&
				!ft_strequ(((t_file *)entries->content)->name, ".") &&
				!ft_strequ(((t_file *)entries->content)->name, ".."))
			print_dir_contents(file_list, entries, opts);
	}
	ft_lstdel(&entries, ft_lst_free_contents);
}

static void		process_dir_contents(t_list *file_list, t_opt *opts,
												t_list *prev, int list_len)
{
	if (!ft_strequ(".", ((t_file *)file_list->content)->name))
	{
		if (prev)
			ft_printf("\n");
		if (list_len > 1)
			ft_printf("%s:\n", ((t_file *)file_list->content)->name);
	}
	print_dir_contents(NULL, file_list, opts);
}

/*
** Takes the list 
*/

void			process_arguments(t_list *file_list, t_opt *opts, int list_len)
{
	t_list		*prev;
	int			info[7];

	prev = NULL;
	calc_col_widths_get_dev_info(file_list, info);
	while (file_list)
	{
		if (S_ISDIR(((t_file *)file_list->content)->stats.st_mode))
			process_dir_contents(file_list, opts, prev, list_len);
		else
		{
			if (opts->l)
				print_w_stats((t_file *)file_list->content, NULL, opts, info);
			else
				ft_printf("%s\n", ((t_file *)file_list->content)->name);
		}
		prev = file_list;
		file_list = file_list->next;
	}
}
