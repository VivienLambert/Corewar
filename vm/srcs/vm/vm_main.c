/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:21:58 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/30 20:58:02 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "../libft/libft.h"
#include "options.h"

int			main(int ac, char *av[])
{
	t_vm	vm;
	int		err;

	ft_bzero(&vm, sizeof(vm));
	init_err(&vm, &err);
	if (ac < 3 || (err = options(ac, av, &vm))
		|| (err = display_init(&vm))
		|| (err = create_arena(&vm)))
	{
		if (err)
			ft_putstr_fd(vm.err[err], 2);
		if (err < ERR_OPEN)
			ft_putstr_fd(vm.err[USAGE], 2);
		return (-1);
	}
	if (vm.options & OPTMAJV)
		ft_printf("OK");
	game_cycle(&vm);
	close_ncurse_display(&vm);
	kill_unactive_processes(&vm, 1);
	return (0);
}
