/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:33:37 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/09 14:54:41 by vlambert         ###   ########.fr       */
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

void	print_action(t_vm *vm, t_proc *proc, char *action)
{
	if (!(vm->options & OPTV))
		return ;
	ft_putstr(vm->players[proc->player].color);
	ft_printf("Processus %3d from player %d is doing a %s",
		proc->number, proc->player + 1, action);
	if (ft_strcmp(action, "life"))
		ft_putchar('\n');
	ft_putstr(_RESET_);
}

void	print_dump(t_vm *vm)
{
	int		i;

	i = 0;
	ft_printf("\nDump at cycle %d:\n\n", vm->cycles_limit);
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != 0)
			ft_putchar('\n');
		else if (i != 0)
			ft_putchar(' ');
		if (i % 64 == 0)
			ft_printf("0x%04x : ", i);
		if (vm->mem_infos_code[i] != -1)
			ft_putstr(vm->players[(int)(vm->mem_infos_code[i])].color);
		ft_printf("%02x", vm->mem[i]);
		ft_putstr(_RESET_);
		i++;
	}
	ft_putchar('\n');
}

void	print_winner(t_vm *vm)
{
	print_arena_govisu(vm, 1);
	if (vm->options & OPTZ || vm->options & OPTMAJV)
		return ;
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
