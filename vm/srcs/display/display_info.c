/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 18:55:11 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/27 16:37:39 by bopopovi         ###   ########.fr       */
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
		wmove(vm->display.info.contents,
			VM_INFO_SIZE + (PLAYER_INFO_SIZE * i), 0);
		wprintw(vm->display.info.contents, "PLAYER [%d] : ", tmp->number);
		wattron(vm->display.info.contents, COLOR_PAIR(i + 1));
		wprintw(vm->display.info.contents, "%s\n", tmp->name);
		wattroff(vm->display.info.contents, COLOR_PAIR(i + 1));
		wprintw(vm->display.info.contents, "Period lives : %d\n",
			tmp->period_lives);
		wprintw(vm->display.info.contents, "Last lives : %d\n",
			tmp->last_p_lives);
		wprintw(vm->display.info.contents, "Processes : %d\n",
			tmp->alive_proc);
		i++;
	}
}

void	display_vm_info(t_vm *vm)
{
	wmove(vm->display.info.contents, 0, 0);
	wattron(vm->display.info.contents, COLOR_PAIR(0));
	if (vm->display.status.paused)
		wprintw(vm->display.info.contents, "PAUSED\n\n\n");
	else
		wprintw(vm->display.info.contents, "RUNNING\n\n\n");
	wprintw(vm->display.info.contents, "CURRENT CYCLE : %d\n\n\n",
		vm->cycles);
	wprintw(vm->display.info.contents, "PERIOD CYCLES : %d\n\n\n",
		vm->cycle_to_die - vm->period_cycles);
	wprintw(vm->display.info.contents, "LAST LIFE : ");
	if (vm->last_player_alive >= 0)
	{
		wattron(vm->display.info.contents,
			COLOR_PAIR(vm->last_player_alive + 1));
		wprintw(vm->display.info.contents, "%s\n\n",
			vm->players[vm->last_player_alive].name);
		wattroff(vm->display.info.contents,
			COLOR_PAIR(vm->last_player_alive + 1));
	}
	wattroff(vm->display.info.contents, COLOR_PAIR(0));
}

void	display_speed(t_vm *vm)
{
	wmove(vm->display.info.contents, INF_H - 1, 0);
	wprintw(vm->display.info.contents, "%d cycles/second\n", vm->display.speed);
}

void	display_winner(t_vm *vm)
{
	char	*winner_name;
	int		winner_id;

	wmove(vm->display.info.contents,
		VM_INFO_SIZE + (PLAYER_INFO_SIZE * vm->players_nbr), 0);
	if (vm->last_player_alive < 0)
		wprintw(vm->display.info.contents, "IT'S A DRAW\n");
	else
	{
		winner_id = vm->last_player_alive;
		winner_name = vm->players[vm->last_player_alive].name;
		wprintw(vm->display.info.contents, "WINNER IS :\n\n");
		wattron(vm->display.info.contents, COLOR_PAIR(winner_id + 1));
		wprintw(vm->display.info.contents, "%s\n", winner_name);
		wattroff(vm->display.info.contents, COLOR_PAIR(winner_id + 1));
	}
	wrefresh(vm->display.info.contents);
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
