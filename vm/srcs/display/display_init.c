/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 21:13:13 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/28 17:40:01 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"

void		close_ncurse_display(t_vm *vm)
{
	char c;

	if (vm->options & OPTZ)
	{
		while (vm->display.status.exit != 1 && (c = getch()) != 'q')
			;
		delwin(vm->display.info.contents);
		delwin(vm->display.info.container);
		delwin(vm->display.memory.contents);
		delwin(vm->display.memory.container);
		endwin();
	}
}

int			new_win(t_win *new, int coord[4])
{
	ft_bzero(new, sizeof(*new));
	if (!(new->container = newwin(coord[0] + 2, coord[1] + 3,
		coord[2], coord[3])))
		return (1);
	box(new->container, 0, 0);
	new->contents = derwin(new->container, coord[0], coord[1], 1, 2);
	wrefresh(new->container);
	wrefresh(new->contents);
	return (0);
}

void		init_ncurse_colors(void)
{
	start_color();
	init_color(COLOR_WHITE, 800, 800, 800);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, 4, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_GREEN);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_RED);
	init_pair(8, COLOR_BLACK, COLOR_CYAN);
	init_pair(9, 8, COLOR_BLACK);
}

void		ncurse_setup(void)
{
	initscr();
	noecho();
	curs_set(false);
	cbreak();
	init_ncurse_colors();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	refresh();
}

int			display_init(t_vm *vm)
{
	if (vm->options & OPTZ)
	{
		ncurse_setup();
		if (new_win(&vm->display.memory, (int[4]){MEM_H, MEM_W, 0, 0}) != 0)
			return (ERR_NCURSE);
		if (new_win(&vm->display.info,
			(int[4]){INF_H, INF_W, 0, MEM_W + 4}) != 0)
			return (ERR_NCURSE);
		vm->display.status.paused = 1;
		vm->display.status.fast_forward = 0;
		vm->display.speed = 50;
	}
	return (0);
}
