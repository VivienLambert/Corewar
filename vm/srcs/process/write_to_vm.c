/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_vm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:32:33 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/30 19:00:20 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	write_byte_to_vm(t_vm *vm, unsigned int address, char byte)
{
	unsigned int real_address;

	real_address = (unsigned int)(address % MEM_SIZE);
	local_dbg(0, "Write byte 0x%02hhx at address %u\n",
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

void	write_to_vm(t_vm *vm, int address, int write, int write_size,
	int player_id)
{
	int i;
	unsigned int unsign_addr;

	i = 0;
	unsign_addr = (unsigned int)address;
	write_mem_info(vm->mem_infos_code, address, write_size, player_id);
	local_dbg(l_dbg, "%-15s: 0x%0*x (%u) -> ", "VM_WRITE", write_size, write, write);
	local_dbg(l_dbg, "ADDR 0x%08x (%u)\n", unsign_addr, unsign_addr);
	while (i < write_size) /* WHAT IF WRITE_SIZE > 4 ? */
	{
		write_byte_to_vm(vm, ((unsign_addr + (write_size - 1)) - i), (char)write);
		write >>= 8;
		i++;
	}
	display_update_color(vm, address % MEM_SIZE, write_size, player_id);
}
