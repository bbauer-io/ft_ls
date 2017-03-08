/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 15:24:38 by bbauer            #+#    #+#             */
/*   Updated: 2017/01/30 06:35:59 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the number of digits stored in a number. Useful for preparing an
** array of chars to hold a number, particulary when other formatting may be
** involved (I created this functionfor for use within ft_printf).
** NOTE: Does NOT account for a '-' or '+' sign in the result.
*/

size_t			ft_nbrlen(int nbr)
{
	size_t		len;

	if (nbr == 0)
		return (0);
	len = 1;
	while (nbr /= 10)
		len++;
	return (len);
}
