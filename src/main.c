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

static void		read_options(int argc, char **argv, t_opt *opts)
{
	int		i;
	int		j;

	i = 1;
	while (i++ < argc)
	{
		j = 0;
		while (argv[i][0] == '-' && argv[i][j++] != '\0')
		{
			if (!ft_strchr("alrRt", argv[i][j]))
			{
				ft_putstr_fd("ft_ls: illegal option -- ", 2);
				write(2, &argv[i][j], 1);
				ft_putstr_fd("\nusage: ft_ls [-alrRt] [file ...]\n", 2);
				exit(1);
			}
			opts->a = (argv[i][j] == 'a' ? 1 : opts->a);
			opts->l = (argv[i][j] == 'l' ? 1 : opts->l);
			opts->r = (argv[i][j] == 'r' ? 1 : opts->r);
			opts->up_r = (argv[i][j] == 'R' ? 1 : opts->up_r);
			opts->t = (argv[i][j] == 't' ? 1 : opts->t);
		}
	}
}

int				main(int argc, char **argv)
{
	t_opt		opts;

	ft_bzero(&opts, sizeof(t_opt));
	read_options(argc, argv, &opts);


}
