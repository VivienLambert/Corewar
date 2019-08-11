/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:19:58 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/22 21:05:30 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "proc.h"

void	dbg_print_addr(bool debug, t_op op, t_proc *proc, unsigned int p1,
	unsigned int p2)
{
	unsigned int	addr;
	short			added;

	added = (short)((short)p1 + (short)p2);
	if (op.addr_restrict)
		added = added % IDX_MOD;
	addr = (proc->pc + added);
	local_dbg(debug, "%-15s: ", "ADDR");
	local_dbg(debug, "(%u ", proc->pc);
	local_dbg(debug, "+ ");
	local_dbg(debug, "(%hd ", p1);
	local_dbg(debug, "+ ");
	local_dbg(debug, "%hd) ", p2);
	if (op.addr_restrict)
		local_dbg(debug, "%% %u", IDX_MOD);
	local_dbg(debug, ") ");
	local_dbg(debug, "%% %u ", MEM_SIZE);
	local_dbg(debug, "= %u\n", addr);
}

void	dbg_print_dir_load(bool debug, char *msg, unsigned int load)
{
	local_dbg(debug, "%-15s: ", msg);
	local_dbg(debug, "0x%08x ", load);
	local_dbg(debug, "(%u)\n", load);
}

void	dbg_print_math(bool debug, char op, unsigned int p1, unsigned int p2,
	unsigned int result)
{
	local_dbg(debug, "%-15s: ", "OPERATION");
	local_dbg(debug, "0x%08x ", p1);
	local_dbg(debug, "%c ", op);
	local_dbg(debug, "0x%08x ", p2);
	local_dbg(debug, "(%hu ", p1);
	local_dbg(debug, "%c ", op);
	local_dbg(debug, "%hu)\n", p2);
	local_dbg(debug, "%-15s: ", "RESULT");
	local_dbg(debug, "0x%08x ", result);
	local_dbg(debug, "(%hu)\n", result);
}

void	dbg_print_ind_load(bool debug, char *msg, unsigned int addr, unsigned int load)
{
	local_dbg(debug, "%-15s: ", msg);
	local_dbg(debug, "[0x%08x]->0x%04hx ", addr, load);
	local_dbg(debug, "([%u]->[%hu])\n", addr, load);
}

void	dbg_print_proc_head(bool debug, t_vm *vm, t_proc *process)
{
	local_dbg(debug, "{green}-----------------------------------------\n{eoc}");
	local_dbg(debug, "{green}[CYCLE %d]{eoc} ", vm->cycles);
	local_dbg(debug, "{green}[PLAYER %d]{eoc} ", process->player + 1);
	local_dbg(debug, "{green}[PROCESS %d]{eoc} ", process->number);
	local_dbg(debug, "{green}[PC %d]{eoc}\n\n", process->pc);
}

void	dbg_print_proc_end(bool debug, t_vm *vm, t_proc *process)
{
	(void)vm;
	local_dbg(debug, "\n{green}[PC %d]{eoc}\n", process->pc);
	local_dbg(debug, "{green}-----------------------------------------\n{eoc}");
	local_dbg(debug, "\n");
}

void	dbg_print_params_head(bool debug)
{
	local_dbg(debug, "{blue}-----------------------------------------\n{eoc}");
	local_dbg(debug, "{blue}[READ PARAMETERS]{eoc}\n\n");
}

void	dbg_print_instruction_head(bool debug, char *op)
{
	local_dbg(debug, "{magenta}-----------------------------------------\n{eoc}");
	local_dbg(debug, "{magenta}[%s]{eoc}\n\n", op);
}

void	local_dbg(bool debug, const char *fmt_msg, ...)
{
	va_list ap;

	if (debug == true && GLOBAL_DBG == 1 && VISU_ON == 0)
	{
		va_start(ap, fmt_msg);
		ft_vdprintf(2, fmt_msg, ap);
		va_end(ap);
	}
}


