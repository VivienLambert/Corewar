/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 14:06:21 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 16:56:20 by ayguillo         ###   ########.fr       */
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

static int	ft_argverif(char **split, t_asm *tasm)
{
	if (!split[1])
		return (ft_syntax(NULL, tasm, split[0][ft_strlen(split[0])]));
	if (!ft_strcmp(split[0], "live"))
		return (ft_paramd(split, tasm, DIR_SIZE));
	else if (!ft_strcmp(split[0], "aff"))
		return (ft_paramrg(split, tasm));
	else if (!ft_strcmp(split[0], "zjmp") || !ft_strcmp(split[0], "lfork")
			|| !ft_strcmp(split[0], "fork"))
		return (ft_paramd(split, tasm, DIR_SIZE / 2));
	else if (!ft_strcmp(split[0], "ld") || !ft_strcmp(split[0], "lld"))
		return (ft_paramld(split, tasm));
	else if (!ft_strcmp(split[0], "st"))
		return (ft_paramst(split, tasm));
	else if (!ft_strcmp(split[0], "add") || !ft_strcmp(split[0], "sub"))
		return (ft_param3rg(split, tasm));
	else if (!ft_strcmp(split[0], "and") || !ft_strcmp(split[0], "or")
			|| !ft_strcmp(split[0], "xor"))
		return (ft_paramcomp(split, tasm));
	else if (!ft_strcmp(split[0], "ldi") || !ft_strcmp(split[0], "lldi"))
		return (ft_paramldi(split, tasm));
	else if (!ft_strcmp(split[0], "sti"))
		return (ft_paramsti(split, tasm));
	return (0);
}

static char	**ft_instok(t_asm *tasm, char **trim)
{
	char	**split;

	split = NULL;
	if (!(split = ft_splitandspaces(*trim, SEPARATOR_CHAR)))
	{
		ft_free(&split, 2, &(tasm->gnl), NULL);
		return (NULL);
	}
	if (!(tasm->op->nbarg = ft_isinst(split[0])))
	{
		ft_free_tab2d(&split);
		tasm->error = 2;
		ft_syntax(trim, tasm, 0);
		return (NULL);
	}
	if (!(ft_separator(trim, tasm->op->nbarg - 1, tasm)))
	{
		ft_free_tab2d(&split);
		return (NULL);
	}
	return (split);
}

static int	ft_argandsearch(char ***split, t_asm *tasm)
{
	if (!(ft_argverif(*split, tasm)))
	{
		ft_free_tab2d(split);
		ft_strdel(&(tasm->gnl.line));
		return (0);
	}
	if (!(ft_searchlabel(tasm, 0)))
	{
		ft_free_tab2d(split);
		return (0);
	}
	return (1);
}

int			ft_instructions(char **trim, t_asm *tasm)
{
	char	*strim;
	char	**split;

	split = NULL;
	strim = NULL;
	if (!(strim = ft_strtrim(*trim)))
		return (ft_free(NULL, 2, &(tasm->gnl), trim));
	ft_strdel(trim);
	if (!(strim[0]))
	{
		ft_strdel(&strim);
		return (1);
	}
	if (!(split = ft_instok(tasm, &strim)))
	{
		ft_free_tab2d(&split);
		ft_strdel(&(tasm->gnl.line));
		ft_strdel(&strim);
		return (0);
	}
	ft_strdel(&strim);
	if (!(ft_argandsearch(&split, tasm)))
		return (0);
	ft_free_tab2d(&split);
	return (1);
}
