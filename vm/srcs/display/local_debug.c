/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:19:58 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/13 14:33:09 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "proc.h"

void	dbg_print_proc_head(int debug, t_vm *vm, t_proc *process)
{
	local_dbg(debug, "{green}-----------------------------------------\n{eoc}");
	local_dbg(debug, "{green}[CYCLE %d]{eoc} ", vm->cycles);
	local_dbg(debug, "{green}[PLAYER %d]{eoc} ", process->player + 1);
	local_dbg(debug, "{green}[PROCESS %d]{eoc} ", process->number);
	local_dbg(debug, "{green}[PC %d]{eoc}\n\n", process->pc);
}

void	dbg_print_proc_end(int debug, t_vm *vm, t_proc *process)
{
	(void)vm;
	local_dbg(debug, "\n{green}[PC %d]{eoc}\n", process->pc);
	local_dbg(debug, "{green}-----------------------------------------\n{eoc}");
	local_dbg(debug, "\n");
}

void	dbg_print_params_head(int debug)
{
	local_dbg(debug, "{blue}-----------------------------------------\n{eoc}");
	local_dbg(debug, "{blue}[READ PARAMETERS]{eoc}\n\n");
}

void	dbg_print_instruction_head(int debug, char *op)
{
	local_dbg(debug,
			"{magenta}-----------------------------------------\n{eoc}");
	local_dbg(debug, "{magenta}[%s]{eoc}\n\n", op);
}

void	local_dbg(int debug, const char *fmt_msg, ...)
{
	va_list ap;

	if (debug == OPTD)
	{
		va_start(ap, fmt_msg);
		ft_vdprintf(2, fmt_msg, ap);
		va_end(ap);
	}
}
