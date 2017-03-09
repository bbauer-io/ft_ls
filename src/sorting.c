#include "ft_ls.h"

int				cmp_alpha(t_file *p1, t_file *p2, int reverse_order)
{
	int			cmp_result;

	cmp_result = (ft_strcmp(p1->name, p2->name));
	if (reverse_order)
		return (cmp_result < 0 ? 1 : 0);
	else
		return (cmp_result > 0 ? 1 : 0);
}

int				cmp_chrono(t_file *p1, t_file *p2, int reverse_order)
{
	if (p1->stats.st_mtimespec.tv_sec == p2->stats.st_mtimespec.tv_sec)
	{
		if (p1->stats.st_mtimespec.tv_nsec == p2->stats.st_mtimespec.tv_nsec)
			return (cmp_lex(p1, p2, reverse_order));
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
