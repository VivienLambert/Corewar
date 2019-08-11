/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 09:01:50 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/09 16:44:07 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "../libft/libft.h"

void		init_process(t_vm *vm, unsigned int pc, t_proc *new)
{
	new->pc = pc % MEM_SIZE;
	new->op_pc = new->pc;
	new->waiting = -1;
	if (vm->proc)
		new->number = vm->proc->number + 1;
	else
		new->number = 1;
	vm->players[new->player].alive_proc += 1;
}

int			add_process(t_vm *vm, int player, unsigned int pc, t_proc *src)
{
	t_proc	*new;

	if (!(new = ft_memalloc(sizeof(t_proc))))
	{
		ft_putstr_fd("vm_process.c: add_process:", 2);
		return (ERR_MALLOC);
	}
	if (src)
		ft_memcpy(new, src, sizeof(t_proc));
	else
	{
		new->regs[0] = vm->players[player].number;
		new->player = player;
	}
	init_process(vm, pc, new);
	new->next = vm->proc;
	vm->proc = new;
	if (vm->options & OPTD)
		ft_dprintf(2, "New process %d from %d carry %d pc %d\n",
			new->number, src ? src->number : 0, new->carry, pc);
	return (0);
}

static void	rechain(t_vm *vm, t_proc **tmp, t_proc **tmp_prev,
	t_proc **to_free)
{
	if (vm->proc == *to_free)
		vm->proc = vm->proc->next;
	else if (*to_free && *tmp_prev)
		(*tmp_prev)->next = (*to_free)->next;
	else
		*tmp_prev = *tmp;
}

void		kill_unactive_processes(t_vm *vm, int end)
{
	t_proc	*tmp;
	t_proc	*tmp_prev;
	t_proc	*to_free;

	tmp = vm->proc;
	to_free = NULL;
	tmp_prev = NULL;
	while (tmp)
	{
		if (tmp->period_lives == 0 || end)
			to_free = tmp;
		else
			tmp->period_lives = 0;
		rechain(vm, &tmp, &tmp_prev, &to_free);
		tmp = tmp->next;
		if (to_free)
		{
			vm->players[to_free->player].alive_proc -= 1;
			ft_memdel((void **)&to_free);
		}
	}
}
