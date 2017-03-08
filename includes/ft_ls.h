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

typedef struct		s_opt
{
	t_bool			l;
	t_bool			up_r;
	t_bool			a;
	t_bool			r;
	t_bool			t;
}					t_opt;

#endif
