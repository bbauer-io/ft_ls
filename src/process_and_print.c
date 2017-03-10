/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_and_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 13:46:02 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/09 21:14:46 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** Prints the total number of blocks used by all files in the directory, just
** like the name says. I added a feature that grabs the blocksize and Prints
** that as well, which adds a little meaning to the number.
*/

static void		print_blocks_total(t_list *file_list)
{
	blkcnt_t	total;
	int			blksize;


	total = 0;
	if (file_list)
		blksize = ((t_file *)file_list->content)->stats.st_blksize;
	while (file_list)
	{
		total += ((t_file *)file_list->content)->stats.st_blocks;
		file_list = file_list->next;
	}
	ft_printf("total %zu blocks (%ukb blocksize)\n", total, blksize);
}

/*
** Prints the total number of blocks used by all files in the directory, then
** proceeds to open the directory and read its contents, creating a list with
** the results and each file's lstat() call results. The list is sorted and
** THE REST OF THE FUNCTION LOOKS EXACTLY LIKE process_arguments() !! - perhaps
** that funciton is reusable instead of explore_all_subdirectories()...
*/

static void		print_dir_contents(t_list *parent, t_list *file_list,
																t_opt *opts)
{
	t_list		*entries;
	t_list		*tmp_entries;
	int			info[7];

	if (!(entries = open_directory(parent, file_list, opts)))
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
		explore_all_subdirectories(entries, file_list, opts);
}

/*
** This function calls it's parent function for each directory found inside the
** present directory, causing all subdirectories to be explored recursively.
*/

void			explore_all_subdirectories(t_list *entries, t_list *file_list,
																t_opt *opts)
{
	while (entries)
	{
		if (S_ISDIR(((t_file *)entries->content)->stats.st_mode) &&
				!ft_strequ(((t_file *)entries->content)->name, ".") &&
				!ft_strequ(((t_file *)entries->content)->name, ".."))
			print_dir_contents(file_list, entries, opts);
		entries = entries->next;
	}
	ft_lstdel(&entries, ft_lst_free_contents);
}

/*
** Prints a newline (if this is not the first directory listed) and the name of
** the directory before calling a function to print the directory's contents.
*/

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
** Takes the list of arguments/files and their stats, then compares the strlen()
** of each field in in the stats struct that will be printed in order to
** determine the field width when printing. If any of the arguments specified
** are directories, a function will be called to explore and list the contents.
** If -l was specified, a function will be called to write details about each
** file. Otherwise (-l not specified and is a file) the filenames will each be
** printed.
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
