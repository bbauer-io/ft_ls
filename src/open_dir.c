/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 19:25:46 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/09 22:24:00 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*
** This function formats the name of the filename for printing by combining the
** file name and full directory path.
*/

static t_list	*modify_folder_name(t_list *parent, t_list *file_list)
{
	char			*parent_folder;
	char			*parent_name;
	char			*file_name;

	parent_folder = NULL;
	if (parent)										 // will there ever not be a parent name?
		parent_name = ft_strdup(((t_file *)parent->content)->name);
	file_name = ft_strdup(((t_file *)file_list->content)->name);
	if (parent && (!ft_strequ(parent_name, file_name)))
	{
		parent_folder = ft_strjoin(parent_name, file_name);
		file_name = ft_strjoin(parent_folder, "/");
	}
	else
		file_name = ft_strjoin(file_name, "/");
	if (parent && !ft_strequ("./", file_name))
		ft_printf("\n%.*s:\n", ft_strlen(file_name) - 1, file_name); // WHY MINUS ONE!?!?!?
	free(((t_file *)file_list->content)->name);
	((t_file *)file_list->content)->name = file_name;
	if (parent)
		free(parent_name);
	free(parent_folder);
	return (file_list);
}

/*
** Reads a directory one file at a time  and saves the contents to a new list of
** files with stats. Files whose names begin with '.' are ignored unless the -a
** option is specified.
*/

static t_list	*read_directory(DIR *directory, t_list *file_list, t_opt *opts)
{
	struct dirent	*file;
	t_file			*current;
	t_list			*entries;

	entries = NULL;
	current = (t_file *)ft_memalloc(sizeof(t_file));
	file = readdir(directory);
	while (file)
	{
		if (opts->a || file->d_name[0] != '.')
		{
			current->name = ft_strdup(file->d_name);
			lstat(ft_strjoin(((t_file *)file_list->content)->name,
											file->d_name), &current->stats);
			ft_lst_append(&entries, ft_lstnew(current, sizeof(t_file)));
		}
		file = readdir(directory);
	}
	free(current);
	return (entries);
}

/*
** Opens a directory stream and passes it to read_directory to extract the
** contents to a list, then closes the directory stream.
*/

t_list			*open_directory(t_list *parent, t_list *file_list, t_opt *opts)
{
	DIR				*directory;
	t_list			*entries;
	char			*file_name;

	entries = NULL;
	file_name = ft_strdup(((t_file *)file_list->content)->name);
	file_list = modify_folder_name(parent, file_list);
	directory = opendir(((t_file *)file_list->content)->name);
	if (!directory)
	{
		ft_printf("ft_ls: %s: %s", file_name, strerror(errno));
		return (NULL);
	}
	free(file_name);
	entries = read_directory(directory, file_list, opts);
	closedir(directory);
	return (entries);
}
