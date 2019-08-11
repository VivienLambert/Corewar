/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_reset_pc_colors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:58:31 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/02 15:00:35 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"

void	display_reset_pc_colors(t_vm *vm)
{
	int			i;
	t_color		*tmp;

	i = 0;
	while (i < MEM_SIZE)
	{
		tmp = &vm->display.color_map[i];
		tmp->pc = 0;
		i++;
	}
}
