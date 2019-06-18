/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:28:13 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/18 13:46:03 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/options.h"
#include "../includes/vm.h"
#include "../libft/libft.h"
#include "../includes/errors.h"

static int  player_exists(int player_nbr, t_vm *vm)
{
    int     i;

    i = 0;
    while (i < MAX_PLAYERS)
    {
        if (vm->players[i].number == player_nbr)
            return (1);
        i++;
    }
    return (0);
}

static int  opt_dump(int ac, char *av[], t_vm *vm, int i)
{
    int nbr;

    if (vm->cycles_limit)
        return (ERR_DBLDUMP);
    if (i + 1 < ac && (nbr = ft_atoi(av[i + 1])) > 0)
        vm->cycles_limit = nbr;
    else
        return (ERR_DUMPVAL);
    return(0);
}

static int  opt_n(int ac, char *av[], t_vm *vm, int i)
{
    int nbr;

    if (vm->players[vm->players_nbr].number)
        return (ERR_TWONBR);
    if (i < ac && (nbr = ft_atoi(av[i])) > 0 && !player_exists(nbr, vm))
        vm->players[vm->players_nbr].number = nbr;
    else
        return (ERR_BADNBR);
    return (0);
}

static int  opt_others(int ac, char *av[], t_vm *vm, int i)
{
    int j;

    j = 0;
    while (av[i][++j])
    {
        if (av[i][j] == 'V')
            vm->options = vm->options | OPTMAJV;
        else if (av[i][j] == 'v')
            vm->options = vm->options | OPTV;
        else if (av[i][j] == 'd')
            vm->options = vm->options | OPTD;
        else
            return (ERR_BADARG);
    }
    return (j != 1 ? 0 : ERR_BADARG);
}

int         options(int ac, char *av[], t_vm *vm)
{
    int i;
    int err;

    i = 0;
    while (++i < ac)
    {
        if (av[i][0] == '-')
        {
            if (!ft_strcmp(av[i], "dump"))
                err = opt_dump(ac, av, vm, i);
            else if (av[i][1] == 'n' && !(av[i][2]))
            {
                ++i;
                err = opt_n(ac, av, vm, i);
            }
            else
                err = opt_others(ac, av, vm, i);
        }
        else
        {
            ft_printf("%s\n", av[i]);
            vm->players_nbr += 1;
            /*creer fonction pour ajout du nom et lecture .cor */
        }
        if (err)
            return (err);
    }
    return (0);
}