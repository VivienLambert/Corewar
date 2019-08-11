/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_update_pc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 19:00:54 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/02 15:09:10 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"

void	display_update_pc(t_vm *vm, unsigned int pc, int player_id)
{
	unsigned int real_pc;

	real_pc = (pc % MEM_SIZE);
	if (vm->options & OPTZ)
		vm->display.color_map[real_pc].pc = 4 + (player_id + 1);
}
