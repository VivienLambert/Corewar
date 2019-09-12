/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_load_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:14:48 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/28 17:39:34 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"
#include "options.h"

void	display_load_player(t_vm *vm, t_player player, int player_id,
	unsigned int start)
{
	if (vm->options & OPTZ)
	{
		display_update_color(vm, start, player.size, player_id);
		display_update_pc(vm, start, player_id);
	}
}
