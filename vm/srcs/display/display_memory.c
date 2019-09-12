/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:10:48 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/22 20:28:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"
#include "options.h"
#include <stdlib.h>

int		display_get_color(t_vm *vm, int position)
{
	int color;

	if (vm->display.color_map[position].highlight > 0)
		vm->display.color_map[position].highlight -= 1;
	if (vm->display.color_map[position].pc > 0)
		color = vm->display.color_map[position].pc;
	else if (vm->display.color_map[position].code > 0)
		color = vm->display.color_map[position].code;
	else
		color = 9;
	return (color);
}

void	win_print_memory(t_vm *vm)
{
	int	color;
	int pc;

	pc = 0;
	wmove(vm->display.memory.contents, 0, 0);
	while (pc < MEM_SIZE)
	{
		color = display_get_color(vm, pc);
		wattron(vm->display.memory.contents, COLOR_PAIR(color));
		if (vm->display.color_map[pc].highlight > 0 && color < 5)
			wattron(vm->display.memory.contents, A_BOLD);
		wprintw(vm->display.memory.contents, "%02hhx", vm->mem[pc]);
		wattroff(vm->display.memory.contents, COLOR_PAIR(color));
		wattroff(vm->display.memory.contents, A_BOLD);
		if (pc + 1 < MEM_SIZE)
			wprintw(vm->display.memory.contents, " ");
		pc++;
	}
}

void	display_memory(t_vm *vm)
{
	if (vm->options & OPTZ)
	{
		win_print_memory(vm);
		wrefresh(vm->display.memory.contents);
	}
}
