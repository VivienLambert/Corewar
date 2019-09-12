/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:33:37 by vlambert          #+#    #+#             */
/*   Updated: 2019/09/10 13:14:27 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "options.h"
#include "../libft/libft.h"
#include "../libft/color.h"

void	intro_champs(t_vm *vm)
{
	int i;

	if (vm->options & OPTMAJV || vm->options & OPTZ)
		return ;
	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->players_nbr)
	{
		ft_putstr(vm->players[i].color);
		ft_printf("* Player %d, wheighing %d bytes, \"%s\" (\"%s\") !\n",
			i + 1, vm->players[i].size, vm->players[i].name,
			vm->players[i].comment);
		++i;
	}
	ft_putstr(_RESET_);
	ft_putchar('\n');
}

void	print_action(t_vm *vm, t_proc *proc, char *action, int player)
{
	if (!(vm->options & OPTV))
		return ;
	ft_putstr(vm->players[proc->player].color);
	ft_printf("Processus %3d from player %d is doing a %s at cycle %d",
		proc->number, proc->player + 1, action, vm->cycles);
	if (!ft_strcmp(action, "life"))
	{
		ft_printf("%s for %splayer %d",
			vm->players[proc->player].color, vm->players[player].color,
			player + 1);
	}
	ft_printf("%s\n", _RESET_);
}

void	print_dump(t_vm *vm)
{
	int		i;

	i = 0;
	ft_printf("\nDump at cycle %d:\n\n", vm->cycles - 1);
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			ft_putchar('\n');
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", vm->mem[i]);
		i++;
	}
	ft_putchar('\n');
}

void	print_winner(t_vm *vm)
{
	print_arena_govisu(vm, 1);
	if (vm->options & OPTMAJV)
		return ;
	if (vm->options & OPTZ)
	{
		display_winner(vm);
		return ;
	}
	if (vm->last_player_alive != -1)
	{
		ft_printf("AND THE WINNER IS...\n");
		ft_putstr(vm->players[vm->last_player_alive].color);
		ft_printf(".:! Player %d: \"%s\" !:.\n", (vm->last_player_alive) + 1,
			vm->players[vm->last_player_alive].name);
		ft_putstr(_RESET_);
	}
	else
		ft_printf("It's a draw\nChamps were weaker than ever\n");
	if (vm->cycles_limit != 0 && !(vm->options & (OPTMAJV | OPTZ)))
		print_dump(vm);
}
