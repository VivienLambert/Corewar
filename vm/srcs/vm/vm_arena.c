/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:19:47 by vlambert          #+#    #+#             */
/*   Updated: 2019/09/10 14:19:24 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"
#include "options.h"
#include "display.h"

static void	init_vars(t_vm *vm)
{
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->checks = MAX_CHECKS;
	vm->last_player_alive = -1;
}

int			create_arena(t_vm *vm)
{
	int		i;
	int		start;

	i = 0;
	if (vm->options & OPTMAJV || vm->options & OPTZ)
		ft_memset((void*)vm->mem_infos_code, -1, MEM_SIZE);
	while (i < vm->players_nbr)
	{
		start = i * MEM_SIZE / vm->players_nbr;
		ft_strcpyfast((char *)vm->mem + start, (char *)vm->players[i].code,
			vm->players[i].size);
		display_load_player(vm, vm->players[i], i, start);
		if (vm->options & OPTMAJV || vm->options & OPTZ)
			ft_memset((void*)vm->mem_infos_code + start, i,
				vm->players[i].size);
		if (add_process(vm, i, start, NULL) == ERR_MALLOC)
		{
			kill_unactive_processes(vm, 1);
			return (ERR_MALLOC);
		}
		++i;
	}
	init_vars(vm);
	return (0);
}
