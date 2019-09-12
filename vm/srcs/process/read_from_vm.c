/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_from_vm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 19:07:44 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/05 18:23:57 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

unsigned char	read_byte_from_vm(t_vm *vm, int address)
{
	int				real_address;
	unsigned char	byte;

	real_address = ((unsigned int)address % MEM_SIZE);
	byte = vm->mem[(unsigned int)real_address];
	return (byte);
}

int				read_from_vm(t_vm *vm, int address, int read_size)
{
	int				i;
	int				read;

	i = 0;
	read = 0;
	local_dbg(vm->options & OPTD, "%-15s: %d bytes from 0x%08x (Real : %d)\n", \
		"VM_READ", read_size, address, (address % MEM_SIZE));
	while (i < read_size)
	{
		read <<= 8;
		read += read_byte_from_vm(vm, address + i);
		i++;
	}
	local_dbg(vm->options & OPTD, "%-15s: 0x%0*x (%u)\n", "READ",
		read_size * 2, read, read);
	return (read);
}
