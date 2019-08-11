/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:24:08 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/02 16:01:37 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_live(t_vm *vm, t_proc *process, t_param *params,
	__attribute__((unused))t_op op)
{
	int		live_id;
	int		player;

	dbg_print_instruction_head(l_dbg, "OP_LIVE");
	live_id = params[0].val;
	local_dbg(l_dbg, "Live id : %u\n", live_id);
	process->period_lives += 1;
	vm->period_lives += 1;
	if ((player = get_player_nbr(vm, live_id)) >= 0)
		set_player_alive(vm, process, player);
	else
		local_dbg(l_dbg, "{red}INVALID LIVE ID{eoc}\n");
}
