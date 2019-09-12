/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_debug2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 14:30:08 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/30 16:41:58 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	dbg_print_addr(int debug, t_op op, t_proc *proc, unsigned int p[2])
{
	int		addr;

	if (op.addr_restrict)
		addr = ((int)proc->pc + (int)(p[0] + p[1]) % IDX_MOD);
	else
		addr = proc->pc + (p[0] + p[1]);
	local_dbg(debug, "%-15s: ", "ADDR");
	local_dbg(debug, "(%u ", proc->pc);
	local_dbg(debug, "+ ");
	local_dbg(debug, "(%d ", p[0]);
	local_dbg(debug, "+ ");
	local_dbg(debug, "%d) ", p[1]);
	if (op.addr_restrict)
		local_dbg(debug, "%% %u", IDX_MOD);
	local_dbg(debug, ") ");
	local_dbg(debug, "%% %u ", MEM_SIZE);
	local_dbg(debug, "= %d\n", addr);
}

void	dbg_print_dir_load(int debug, char *msg, unsigned int load)
{
	local_dbg(debug, "%-15s: ", msg);
	local_dbg(debug, "0x%08x ", load);
	local_dbg(debug, "(%u)\n", load);
}

void	dbg_print_math(int debug, char op, unsigned int p[2],
	unsigned int result)
{
	local_dbg(debug, "%-15s: ", "OPERATION");
	local_dbg(debug, "0x%08x ", p[0]);
	local_dbg(debug, "%c ", op);
	local_dbg(debug, "0x%08x ", p[1]);
	local_dbg(debug, "(%hu ", p[0]);
	local_dbg(debug, "%c ", op);
	local_dbg(debug, "%hu)\n", p[1]);
	local_dbg(debug, "%-15s: ", "RESULT");
	local_dbg(debug, "0x%08x ", result);
	local_dbg(debug, "(%hu)\n", result);
}

void	dbg_print_ind_load(int debug, char *msg, unsigned int addr,
		unsigned int load)
{
	local_dbg(debug, "%-15s: ", msg);
	local_dbg(debug, "[0x%08x]->0x%04hx ", addr, load);
	local_dbg(debug, "([%u]->[%hu])\n", addr, load);
}
