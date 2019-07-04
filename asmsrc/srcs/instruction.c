/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:06:21 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/03 14:10:02 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>
#include "../includes/asm.h"

static int	ft_isinst(char *inst)
{
	if (!ft_strcmp(inst, "live") || !ft_strcmp(inst, "zjmp")
				|| !ft_strcmp(inst, "fork") || !ft_strcmp(inst, "lfork")
				|| !ft_strcmp(inst, "aff"))
		return (1);
	else if (!ft_strcmp(inst, "ld") || !ft_strcmp(inst, "st")
				|| !ft_strcmp(inst, "lld"))
		return (2);
	else if (!ft_strcmp(inst, "add") || !ft_strcmp(inst, "sub")
				|| !ft_strcmp(inst, "and") || !ft_strcmp(inst, "or")
				|| !ft_strcmp(inst, "xor") || !ft_strcmp(inst, "ldi")
				|| !ft_strcmp(inst, "sti") || !ft_strcmp(inst, "lldi"))
		return (3);
	return (0);
}

static char	**ft_instok(char **line, char **trim, t_op **op)
{
	char	**split;

	split = NULL;
	if (!(split = ft_splitandspaces(*trim, SEPARATOR_CHAR)))
	{
		ft_free(&split, 2, line, NULL);
		return (NULL);
	}
	if (!((*op)->nbarg = ft_isinst(split[0])))
	{
		ft_freecom(&split, 3, split[0], line);
		return (NULL);
	}
	if (!(ft_separator(trim, (*op)->nbarg - 1, line)))
	{
		ft_free_tab2d(&split);
		return (NULL);
	}
	return (split);
}

int	ft_argverif(char **split, t_op *op)
{
	int i;

	i = 0;
	if (!ft_strcmp(split[0], "live"))
		ft_paramd(split, op, DIR_SIZE);
	else if (!ft_strcmp(split[0], "aff"))
		ft_paramrg(split, op);
	else if (!ft_strcmp(split[0], "zjmp") || !ft_strcmp(split[0], "lfork")
			|| !ft_strcmp(split[0], "fork"))
		ft_paramd(split, op, DIR_SIZE / 2);
	else if (!ft_strcmp(split[0], "ld") || !ft_strcmp(split[0], "lld"))
		ft_paramld(split, op);
	else if (!ft_strcmp(split[0], "st"))
		ft_paramst(split, op);
	else if (!ft_strcmp(split[0], "add") || !ft_strcmp(split[0], "sub"))
		ft_param3rg(split, op);
	else if (!ft_strcmp(split[0], "and") || !ft_strcmp(split[0], "or")
			|| !ft_strcmp(split[0], "xor"))
		ft_paramcomp(split, op);
	else if (!ft_strcmp(split[0], "ldi") || !ft_strcmp(split[0], "lldi"))
		ft_paramldi(split, op);
	else if (!ft_strcmp(split[0], "sti"))
		ft_paramsti(split, op);
	else
		return (0);
	return (1);
}

int			ft_instructions(char **trim, char **line, t_op **op)
{
	char	*strim;
	char	**split;

	if (!(strim = ft_strtrim(*trim)))
		return (ft_free(NULL, 2, line, trim));
	ft_strdel(trim);
	if (!(strim[0]))
		return (1);
	if (!(split = ft_instok(line, &strim, op)))
	{
		ft_strdel(line);
		ft_strdel(&strim);
		return (0);
	}
	ft_strdel(&strim);
	if (!(ft_argverif(split, *op)))
	{
		ft_strdel(line);
		return (0);
	}
	/*
	 ** AFFICHAGE TEST
	 */
	t_op	*tmp;
	tmp = *op;
	while (tmp)
	{
		ft_printf("label %s && instruction = %i, size = %i && addr = %i && code = %i && param = %i\n", tmp->label,
				(tmp)->inst, (tmp)->size, (tmp)->addr, (tmp)->code1, (tmp)->param1);
		(tmp) = (tmp)->next;
	}
	ft_putchar('\n');
	return (1);
}