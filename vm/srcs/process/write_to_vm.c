/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_vm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:32:33 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/13 14:53:01 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

void	write_byte_to_vm(t_vm *vm, unsigned int address, char byte)
{
	unsigned int	real_address;

	real_address = (unsigned int)(address % MEM_SIZE);
	local_dbg(vm->options & OPTD, "Write byte 0x%02hhx at address %u\n",
		byte, real_address);
	vm->mem[real_address] = byte;
}

void	write_mem_info(char *mem_info, unsigned int address, int size,
	int player_id)
{
	int				i;

	i = 0;
	while (i < size)
	{
		mem_info[(address + i) % MEM_SIZE] = player_id;
		i++;
	}
}

void	write_to_vm(t_vm *vm, int address, int write, int player_id)
{
	int				i;
	unsigned int	unsign_addr;
	int				write_size;

	i = 0;
	write_size = 4;
	unsign_addr = (unsigned int)address;
	write_mem_info(vm->mem_infos_code, address, write_size, player_id);
	local_dbg(vm->options & OPTD, "%-15s: 0x%0*x (%u) -> ", "VM_WRITE",
		write_size, write, write);
	local_dbg(vm->options & OPTD, "ADDR 0x%08x (%u)\n",
		unsign_addr, unsign_addr);
	while (i < write_size)
	{
		write_byte_to_vm(vm, ((unsign_addr + (write_size - 1)) - i),
			(char)write);
		write >>= 8;
		i++;
	}
	display_update_color(vm, address % MEM_SIZE, write_size, player_id);
}
