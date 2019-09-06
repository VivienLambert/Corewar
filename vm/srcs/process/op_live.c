/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:24:08 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/06 14:06:36 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static void		verbose_live(t_proc *proc, int live_id)
{
		ft_printf("P %4d | live %d\n", proc->number, live_id);
}

void	op_live(t_vm *vm, t_proc *process, t_param *params, t_op op)
{
	int		live_id;
	int		player;

	(void)op;
	dbg_print_instruction_head(vm->options & OPTD, "OP_LIVE");
	live_id = params[0].val;
	local_dbg(vm->options & OPTD, "Live id : %u\n", live_id);
	if (vm->cycle_to_die > 0)
		process->period_lives += 1;
	vm->period_lives += 1;
	if ((player = get_player_nbr(vm, live_id)) >= 0)
		set_player_alive(vm, process, player);
	else
		local_dbg(vm->options & OPTD, "{red}INVALID LIVE ID{eoc}\n");
	verbose_live(process, live_id);
}
