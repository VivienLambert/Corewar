/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_load_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 18:14:48 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/02 15:11:34 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"
#include "options.h"

/*void	display_write_memory(t_vm *vm, int start, int size, int player_id)
{
	int i;
	int x;
	int y;

	(void)size;
	(void)player_id;
	i = 0;
	y = ((start * 3) / (MEM_W - 4));
	x = (start % (64)) * 3;
	wmove(vm->display.memory.contents, y, x);
	wattron(vm->display.memory.contents, COLOR_PAIR(player_id + 1));
	while (i < size)
	{
		wprintw(vm->display.memory.contents, "%02hhx ", vm->mem[start + i]);
		i++;
	}
	wattroff(vm->display.memory.contents, COLOR_PAIR(0));
}*/

void	display_load_player(t_vm *vm, t_player player, int player_id,
	unsigned int start)
{
	if (vm->options & OPTZ)
	{
		display_update_color(vm, start, player.size, player_id);
		display_update_pc(vm, start, player_id);
	}
}
