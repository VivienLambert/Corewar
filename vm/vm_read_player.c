/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:03:16 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/28 08:34:53 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"
#include "../libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

static int	test_size(char *champ, int fd, t_vm *vm)
{
	if (vm->players[vm->players_nbr].size > CHAMP_MAX_SIZE)
	{
		ft_putstr_fd(champ, 2);
		ft_putstr_fd(" size is too big (max = ", 2);
		ft_putnbr_fd(CHAMP_MAX_SIZE, 2);
		ft_putstr_fd(" yours = ", 2);
		ft_putnbr_fd(vm->players[vm->players_nbr].size, 2);
		ft_putstr_fd(")\n", 2);
		close(fd);
		return (ERR_SIZE);
	}
	close(fd);
	return (0);
}

static int	read_all(char *champ, int fd, t_vm *vm)
{
	unsigned int	temp;
	static int		number = 0;

	if (read(fd, &temp, sizeof(int)) < sizeof(int)
		|| ft_reversebyte(temp, sizeof(int)) != COREWAR_EXEC_MAGIC
		|| read(fd, vm->players[vm->players_nbr].name, PROG_NAME_LENGTH + 4)
			< PROG_NAME_LENGTH + 4
		|| read(fd, &temp, sizeof(int))
			< sizeof(int)
		|| !(vm->players[vm->players_nbr].size = ft_reversebyte(temp,
			sizeof(int)))
		|| read(fd, vm->players[vm->players_nbr].comment, COMMENT_LENGTH + 4)
			< COMMENT_LENGTH + 4
		|| read(fd, vm->players[vm->players_nbr].code,
			vm->players[vm->players_nbr].size + 1)
			!= vm->players[vm->players_nbr].size)
	{
		ft_putstr_fd(champ, 2);
		close(fd);
		return (ERR_CHAMP);
	}
	if (!(vm->players[vm->players_nbr].number))
		vm->players[vm->players_nbr].number = --number;
	vm->players[vm->players_nbr].regs[0] = vm->players[vm->players_nbr].number;
	return (test_size(champ, fd, vm));
}

int			read_champ(char *champ, t_vm *vm)
{
	int				fd;

	if ((fd = open(champ, O_RDONLY)) == -1)
	{
		ft_putstr_fd(champ, 2);
		return (ERR_OPEN);
	}
	return (read_all(champ, fd, vm));
}
