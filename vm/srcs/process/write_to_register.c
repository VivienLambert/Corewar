/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_register.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:27:28 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/20 18:21:24 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	write_to_register(t_proc *process, int register_id, int write)
{
	/* ERROR CASE : Invalid register id */
	if (register_id < 1 || register_id > REG_NUMBER)
		local_dbg(l_dbg, "REG_WRITE INVALID ID : '%d'\n", register_id);
	else
	{
		local_dbg(l_dbg, "%-15s: 0x%08x (%u) -> ", "REG_WRITE", write, write);
		local_dbg(l_dbg, "REG %d\n", register_id);
		process->regs[register_id - 1] = write;
	}
}
