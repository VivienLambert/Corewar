/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:27:05 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/09 14:52:45 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "options.h"
#include "../../../libft/color.h"

__attribute__((unused))static bool l_dbg = 1;

void	set_player_alive(t_vm *vm, t_proc *process, int player)
{
	local_dbg(l_dbg, "Setting player %d as alive\n", player);
	vm->players[player].period_lives += 1;
	vm->last_player_alive = player;
	if (vm->options & OPTV)
	{
		print_action(vm, process, "life");
		ft_putstr(vm->players[process->player].color);
		ft_printf("%s for %splayer %d%s\n",
			vm->players[process->player].color, vm->players[player].color,
			player + 1, _RESET_);
	}
}
