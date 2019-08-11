/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_vm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:07:44 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/20 18:21:23 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

static bool l_dbg = 1;

unsigned char	read_byte_from_vm(t_vm *vm, int address)
{
	int				real_address;
	unsigned char	byte;

	real_address = (address % MEM_SIZE);
	byte = vm->mem[real_address];
	return (byte);
}

int		read_from_vm(t_vm *vm, int address, int read_size)
{
	int i;
	int read;

	i = 0;
	read = 0;
	local_dbg(l_dbg, "%-15s: %d bytes from 0x%08x (Real : %d)\n", \
		"VM_READ", read_size, address, (address % MEM_SIZE));
	while (i < read_size) /* WHAT IF READ_SIZE > 4 ? */
	{
		read <<= 8;
		read += read_byte_from_vm(vm, address + i);
		i++;
	}
	local_dbg(l_dbg, "%-15s: 0x%0*x (%u)\n", "READ", read_size * 2, read, read);
	return (read);
}
