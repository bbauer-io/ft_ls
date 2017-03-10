/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 11:10:25 by bbauer            #+#    #+#             */
/*   Updated: 2017/03/09 17:57:58 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Returns 1 if p1 would come before p2 alphabetically.
** The order can be reversed with the reverse_order option.
*/

int				cmp_alpha(t_file *p1, t_file *p2, int reverse_order)
{
	int			cmp_result;
	char		*tmp1;
	char		*tmp2;

	tmp1 = ft_tolower_str(ft_strdup(p1->name));
	tmp2 = ft_tolower_str(ft_strdup(p2->name));
	cmp_result = (ft_strcmp(tmp1, tmp2));
	free(tmp1);
	free(tmp2);
	if (reverse_order)
		return (cmp_result < 0 ? 1 : 0);
	else
		return (cmp_result > 0 ? 1 : 0);
}

/*
** Returns 1 if the p1's modification time older than p2's modification time.
** That can be reversed with the reverse_order option.
** Comparison is done to the nanosecond if seconds are the same, then
** alphabetically if there is still no difference.
*/

int				cmp_chrono(t_file *p1, t_file *p2, int reverse_order)
{
	if (p1->stats.st_mtimespec.tv_sec == p2->stats.st_mtimespec.tv_sec)
	{
		if (p1->stats.st_mtimespec.tv_nsec == p2->stats.st_mtimespec.tv_nsec)
			return (cmp_alpha(p1, p2, reverse_order));
		if (reverse_order)
			return (p1->stats.st_mtimespec.tv_nsec
				> p2->stats.st_mtimespec.tv_nsec);
		else
			return (p1->stats.st_mtimespec.tv_nsec
				< p2->stats.st_mtimespec.tv_nsec);
	}
	if (reverse_order)
		return (p1->stats.st_mtimespec.tv_sec
			> p2->stats.st_mtimespec.tv_sec);
	else
		return (p1->stats.st_mtimespec.tv_sec
			< p2->stats.st_mtimespec.tv_sec);
}

static void		lst_content_swap(t_list *one, t_list *two)
{
	void		*tmp;

	tmp = one->content;
	one->content = two->content;
	two->content = tmp;
}

/*
** lst_sort() uses the return value of the function passed to it to sort a list.
** I have included functions for alphabetical and chronological sorting.
*/

void			lst_sort(t_list *start, int (*f)(t_file *, t_file *, int),
															int reverse_order)
{
	int			swapped;
	t_list		*left;
	t_list		*right;

	right = NULL;
	if (start == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		left = start;
		while (left->next != right)
		{
			if (f(left->content, left->next->content, reverse_order))
			{
				lst_content_swap(left, left->next);
				swapped = 1;
			}
			left = left->next;
		}
		right = left;
	}
}
