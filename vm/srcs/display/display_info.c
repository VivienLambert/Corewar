/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 18:55:11 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/01 02:49:52 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"

void	display_players_info(t_vm *vm)
{
	int			i;
	t_player	*tmp;

	i = 0;
	while (i < vm->players_nbr)
	{
		tmp = &vm->players[i];
		wmove(vm->display.info.contents, VM_INFO_SIZE + (PLAYER_INFO_SIZE * i), 0);
		wattron(vm->display.info.contents, COLOR_PAIR(i + 1));
		wprintw(vm->display.info.contents, "PLAYER [%d] : ", tmp->number);
		wprintw(vm->display.info.contents, "%s\n", tmp->name);
		wprintw(vm->display.info.contents, "Period lives : %d\n", tmp->period_lives);
		wprintw(vm->display.info.contents, "Last period lives : %d\n", tmp->last_p_lives);
		wprintw(vm->display.info.contents, "Alive processes : %d\n", tmp->alive_proc);
		wattroff(vm->display.info.contents, COLOR_PAIR(i + 1));
		i++;
	}
}

void	display_vm_info(t_vm *vm)
{
	wmove(vm->display.info.contents, 0, 0);
	wprintw(vm->display.info.contents, "CURRENT CYCLE : %d\n", vm->cycles);
	wprintw(vm->display.info.contents, "CYCLES TO DIE : %d\n\n", vm->cycle_to_die);
}

int		speed[9] =
{
	NC_MAX_SPEED - (NC_SPEED_DELTA * 8),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 7),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 6),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 5),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 4),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 3),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 2),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 1),
	NC_MAX_SPEED
};

void	display_speed(t_vm *vm)
{
	wmove(vm->display.info.contents, INF_H - 1, 0);
	wprintw(vm->display.info.contents, "Speed : %d\n", speed[vm->display.speed]);
}

void	display_info(t_vm *vm)
{
	if (vm->options & OPTZ)
	{
		display_vm_info(vm);
		display_players_info(vm);
		display_speed(vm);
		wrefresh(vm->display.info.contents);
	}
}
