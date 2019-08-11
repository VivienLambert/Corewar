/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:43:58 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/06 16:58:09 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_free_tab2d(char ***tab)
{
	int i;

	i = 0;
	if (!(tab) || !(*tab))
		return ;
	while (*tab && tab[0][i])
		free(tab[0][i++]);
	if (*tab)
		free(*tab);
	*tab = NULL;
}
