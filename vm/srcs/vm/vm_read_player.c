/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_read_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:03:16 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/29 15:40:57 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "options.h"
#include "color.h"
#include <fcntl.h>
#include <unistd.h>

static int	read_part(int fd, int length, char *buff)
{
	if (read(fd, buff, length + 4) < length + 4 || buff[length] != 0)
		return (-1);
	return (0);
}

static int	err_champ(char *champ, int fd)
{
	ft_dprintf(2, "%s: ", champ);
	close(fd);
	return (ERR_CHAMP);
}

static int	test_size(char *champ, int fd, t_vm *vm)
{
	if (vm->players[vm->players_nbr].size > CHAMP_MAX_SIZE)
	{
		ft_putstr_fd(champ, 2);
		ft_putstr_fd(" size is too big (max = ", 2);
		ft_putnbr_fd(CHAMP_MAX_SIZE, 2);
		ft_putstr_fd(" yours = ", 2);
		ft_dprintf(2, "%u", vm->players[vm->players_nbr].size);
		ft_putstr_fd(")\n", 2);
		close(fd);
		return (ERR_SIZE);
	}
	return (0);
}

static int	read_all(char *champ, int fd, t_vm *vm)
{
	unsigned int	temp;
	static int		number = 0;

	if ((unsigned long)read(fd, &temp, sizeof(int)) < sizeof(int)
			|| ft_reversebyte(temp, sizeof(int)) != COREWAR_EXEC_MAGIC
			|| read_part(fd, PROG_NAME_LENGTH,
				vm->players[vm->players_nbr].name)
			|| (unsigned long)read(fd, &temp, sizeof(int))
			< sizeof(int)
			|| !(vm->players[vm->players_nbr].size = ft_reversebyte(temp,
					sizeof(int))))
		return (err_champ(champ, fd));
	if (test_size(champ, fd, vm))
		return (ERR_SIZE);
	if (read_part(fd, COMMENT_LENGTH,
				vm->players[vm->players_nbr].comment)
			|| read(fd, vm->players[vm->players_nbr].code,
				vm->players[vm->players_nbr].size + 1)
			!= vm->players[vm->players_nbr].size)
		return (err_champ(champ, fd));
	if (!(vm->players[vm->players_nbr].number))
		vm->players[vm->players_nbr].number = --number;
	close(fd);
	return (0);
}

int			read_champ(char *champ, t_vm *vm)
{
	int				fd;
	int				err;

	if (vm->players_nbr >= MAX_PLAYERS)
		return (ERR_TMCHAMP);
	if ((fd = open(champ, O_RDONLY)) == -1)
	{
		ft_dprintf(2, "%s: ", champ);
		return (ERR_OPEN);
	}
	err = read_all(champ, fd, vm);
	if (vm->options & OPTMAJV)
		ft_strreplace(vm->players[vm->players_nbr].name, ';', ':');
	if (vm->players_nbr == 0)
		ft_strcpy(vm->players[vm->players_nbr].color, _RED_);
	if (vm->players_nbr == 1)
		ft_strcpy(vm->players[vm->players_nbr].color, _GREEN_);
	if (vm->players_nbr == 2)
		ft_strcpy(vm->players[vm->players_nbr].color, _PURPLE_);
	if (vm->players_nbr == 3)
		ft_strcpy(vm->players[vm->players_nbr].color, _YELLOW_);
	return (err);
}
