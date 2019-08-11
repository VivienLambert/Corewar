/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_address.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 18:04:25 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/22 21:03:34 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

unsigned int	calculate_address(t_proc *proc, t_op op, unsigned int p1,
	unsigned int p2)
{
	unsigned int	addr;
	short			added;

	added = ((short)((short)p1 + (short)p2));
	if (op.addr_restrict)
		added = added % IDX_MOD;
	addr = proc->pc + added;
	dbg_print_addr(l_dbg, op, proc, p1, p2);
	return (addr);
}
