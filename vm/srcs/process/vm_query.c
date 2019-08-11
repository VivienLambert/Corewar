/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_query.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/10 17:37:01 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

int		get_player_nbr(t_vm *vm, int player_id)
{
	size_t i;

	i = 0;
	while (i < (size_t)vm->players_nbr)
	{
		if (vm->players[i].number == player_id)
			return (i);
		i++;
	}
	return (-1);
}
