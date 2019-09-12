/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 10:08:21 by vlambert          #+#    #+#             */
/*   Updated: 2019/08/29 15:40:12 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

/*
** Check includes/errors.h for message max size ERR_MSG_SIZE
*/

void	init_err(t_vm *vm, int *err)
{
	*err = 0;
	ft_strcpy(vm->err[USAGE], "Usage: ./corewar [-d || -v || -V || -z] \
[-dump nbr_cycles] [[-n number] champion1.cor] ... Max 4 players\n\
-d: Debug mode(out on stderr, can be cumulated with -V)\n-v: Verbose mode\n\
-V: Visual mode\n-z: Ncurse mode\n");
	ft_strcpy(vm->err[ERR_DBLDUMP], "More than one dump precised\n");
	ft_strcpy(vm->err[ERR_BADARG], "Unknown or incompatible arguments\n");
	ft_strcpy(vm->err[ERR_DUMPVAL], "Dump nbr_cycles is lower than \
one or missing with option -dump\n");
	ft_strcpy(vm->err[ERR_BADNBR], "The player number is lower than 1 or \
missing or the same than another player\n");
	ft_strcpy(vm->err[ERR_NOCHAMP], "No valid champs have been precised\n");
	ft_strcpy(vm->err[ERR_TWONBR], "Two player number were precised \
for a single player\n");
	ft_strcpy(vm->err[ERR_OPEN], "Can't access the champ\n");
	ft_strcpy(vm->err[ERR_CHAMP], "Doesn't seem to be a healthy champion \
(be sure to use our asm)\n");
	ft_strcpy(vm->err[ERR_MALLOC], "Malloc error\n");
	ft_strcpy(vm->err[ERR_NCURSE], "Ncurse has crashed\n");
	ft_strcpy(vm->err[ERR_TMCHAMP], "Too much champions. (Max 4)\n");
}
