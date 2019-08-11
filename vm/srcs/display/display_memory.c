/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 19:10:48 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/02 15:06:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"
#include "options.h"
#include <stdlib.h>

int		display_get_color(t_vm *vm, int position)
{
	int color;

	color = 0;
	if (vm->display.color_map[position].highlight > 0)
	{
		color = vm->display.color_map[position].highlight;
	}
	else if (vm->display.color_map[position].pc > 0)
		color = vm->display.color_map[position].pc;
	else
		color = vm->display.color_map[position].code;
	return (color);
}

void	win_print_memory(t_vm *vm)
{
	int i;
	int	color;
	int pc;

	i = 0;
	pc = 0;
	wmove(vm->display.memory.contents, 0, 0);
	while (pc < MEM_SIZE)
	{
		color = display_get_color(vm, pc);
		wattron(vm->display.memory.contents, COLOR_PAIR(color));
		wprintw(vm->display.memory.contents, "%02hhx", vm->mem[pc]);
		//wprintw(vm->display.memory.contents, "%02hd", color);
		wattroff(vm->display.memory.contents, COLOR_PAIR(color));
		i += 2;
		if (pc + 1 < MEM_SIZE)
		{
			i++;
			wprintw(vm->display.memory.contents, " ");
		}
		else
			i = 0;
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
