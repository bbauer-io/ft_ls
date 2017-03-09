#include "libft.h"

void	ft_lst_free_contents(void *contents, size_t content_size)
{
	if (content)
		free(content);
}
