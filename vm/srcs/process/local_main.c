/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:28:41 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/01 20:15:44 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/proc.h"

static bool l_dbg = 1;

int		placeholder_init_data(t_vm *vm, t_proc *proc)
{
	ft_bzero(vm, sizeof(*vm));
	if (read_champ("zork.cor", vm))
		return (1);


	ft_bzero(proc, sizeof(t_proc));

	local_dbg(l_dbg, "Copying player %d's program in memory\n", 0);
	local_dbg(l_dbg, "Program length : %d bytes\n\n", vm->players[0].size);
	ft_memcpy(vm->mem, vm->players[0].code, vm->players[0].size);
	proc->regs[0] = 0;

	ft_putchar('\n');

	return (0);
}

int		main(void)
{
	t_proc	proc;
	t_vm	vm;

	initscr();
	noecho();
	curs_set(false);
	cbreak();
	start_color();
	if (placeholder_init_data(&vm, &proc))
		return (1);
	init_memory_win(&vm.display.memory);
	int loop = 1;
	while (loop++)
	{
		//display_memory(&vm, );
		process_execute(&vm, &proc);
		//ft_putchar_fd('\n', 2);
	}
	endwin();
	return (0);
}
