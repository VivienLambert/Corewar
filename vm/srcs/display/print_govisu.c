/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_govisu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 09:52:40 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/07 12:03:19 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "vm.h"
#include "options.h"
#include <errno.h>

static void	check_pipe_errors(t_vm *vm)
{
	if (errno)
	{
		kill_unactive_processes(vm, 1);
		perror("Corewar:");
		exit(-1);
	}
}

static void	print_infos_govisu(t_vm *vm)
{
	int		i;

	i = 0;
	ft_printf("---CYCLES---\nCycles: %d\nPeriod cycles: %d / %d\n", vm->cycles,
		vm->period_cycles, vm->cycle_to_die);
	ft_printf("\n---LAST LIFE---\n%s\n",
		(vm->last_player_alive != -1) ?
			vm->players[vm->last_player_alive].name : "Nobody");
	ft_printf("\n---PLAYERS---\n");
	while (i < vm->players_nbr)
	{
		ft_printf("\n---PLAYER[%d]---\n", vm->players[i].number);
		ft_printf("Name: %s\n", vm->players[i].name);
		ft_printf("Period lives: %d\n", vm->players[i].period_lives);
		ft_printf("Last period lives: %d\n", vm->players[i].last_p_lives);
		ft_printf("Number of alive process: %d\n", vm->players[i].alive_proc);
		i++;
	}
	ft_printf(";");
}

static void	check_colors(unsigned int i, t_vm *vm, const char *color_code,
	char *color)
{
	if (color[0] != color_code[0] && color[0] != color_code[1]
		&& color[0] != color_code[2] && color[0] != color_code[3])
		color[0] = 'Z';
	if (vm->mem_infos_code[i] != -1)
		color[1] = color_code[(int)(vm->mem_infos_code[i])];
	else
		color[1] = 'Z';
}

static void	print_arena(t_vm *vm, char *char_set)
{
	unsigned int	i;
	unsigned int	j;
	static char		str[MEM_SIZE * 4 + 2];
	t_proc			*tmp;

	i = 0;
	j = 0;
	ft_bzero(str, MEM_SIZE * 4 + 2);
	tmp = vm->proc;
	while (tmp)
	{
		str[(tmp->pc % MEM_SIZE) * 4] = "RGBY"[tmp->player];
		tmp = tmp->next;
	}
	while (j < MEM_SIZE)
	{
		check_colors(j, vm, "RGPY", str + i);
		i += 2;
		str[i++] = char_set[((unsigned char)vm->mem[j]) / 16];
		str[i++] = char_set[((unsigned char)vm->mem[j]) % 16];
		j += 1;
	}
	str[i++] = ';';
	str[i] = 0;
	ft_putstr(str);
}

void		print_arena_govisu(t_vm *vm, int end)
{
	if (!(vm->options & OPTMAJV))
		return ;
	print_arena(vm, "0123456789abcdef");
	check_pipe_errors(vm);
	if (end && vm->last_player_alive != -1)
		ft_printf("The winner is: \nPlayer[%d]: %s;",
			vm->players[vm->last_player_alive].number,
			vm->players[vm->last_player_alive].name);
	else
		print_infos_govisu(vm);
	check_pipe_errors(vm);
}
