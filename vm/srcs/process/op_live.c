/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:24:08 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/10 13:04:18 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"
#include "vm.h"

static void	set_player_alive(t_vm *vm, t_proc *process, int player)
{
	local_dbg(vm->options & OPTD, "Setting player %d as alive\n", player + 1);
	vm->players[player].period_lives += 1;
	vm->last_player_alive = player;
	if (vm->options & OPTV)
		print_action(vm, process, "life", player);
}

void		op_live(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	int		live_id;
	int		player;

	(void)op;
	dbg_print_instruction_head(vm->options & OPTD, "OP_LIVE");
	live_id = params[0].val;
	local_dbg(vm->options & OPTD, "Live id : %u\n", live_id);
	if (vm->cycle_to_die > 0)
	{
		process->last_live = vm->cycles;
		process->period_lives += 1;
	}
	vm->period_lives += 1;
	if ((player = get_player_nbr(vm, live_id)) >= 0)
		set_player_alive(vm, process, player);
	else
		local_dbg(vm->options & OPTD, "{red}INVALID LIVE ID{eoc}\n");
}
