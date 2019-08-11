/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:00:00 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/01 02:50:45 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"

int		speeds[9] =
{
	NC_MAX_SPEED - (NC_SPEED_DELTA * 8),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 7),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 6),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 5),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 4),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 3),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 2),
	NC_MAX_SPEED - (NC_SPEED_DELTA * 1),
	NC_MAX_SPEED
};

void	display_handle_key(t_vm *vm, char key)
{
	if (key == ' ')
	{
		if (vm->display.status.paused)
			vm->display.status.paused = 0;
		else
			vm->display.status.paused = 1;
	}
	else if (key == 'q')
	{
		endwin();
		exit(0);
	}
	else if (key == 'n')
	{
		if (vm->display.status.paused)
			vm->display.status.paused = 0;
	}
	else if (key == 'k' && vm->display.speed < 8)
		vm->display.speed += 1;
	else if (key == 'j' && vm->display.speed > 0)
		vm->display.speed -= 1;
	display_info(vm);
}

void	display_update(t_vm *vm)
{
	char c;

	c = 0;
	if (vm->options & OPTZ)
	{
		display_info(vm);
		display_memory(vm);
		c = getch();
		if (ft_strchr(NC_KEYS, c))
			display_handle_key(vm, c);
		while (vm->display.status.paused)
		{
			c = getch();
			if (ft_strchr(NC_KEYS, c))
				display_handle_key(vm, c);
		}
		if (!vm->display.status.fast_forward)
		{
			usleep(speeds[vm->display.speed]);
		}
	}
}
