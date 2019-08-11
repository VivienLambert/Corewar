/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reversebyte.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 14:04:27 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/24 17:19:24 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

unsigned int	ft_reversebyte(unsigned int byte, size_t size)
{
	unsigned int	revbyte;
	int				i;

	i = size - 1;
	while (i >= 0)
	{
		((char*)(&revbyte))[i] = ((char*)(&byte))[0];
		byte = byte >> 8;
		i--;
	}
	return (revbyte);
}
