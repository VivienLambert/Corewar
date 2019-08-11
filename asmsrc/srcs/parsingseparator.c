/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingseparator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 12:04:50 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 15:22:22 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../includes/op.h"
#include "../libft/libft.h"
#include <stdlib.h>

static int		ft_islab(char *spaces, int *i, t_asm *tasm)
{
	int	j;

	(*i)++;
	while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
	{
		j = -1;
		while (LABEL_CHARS[++j])
			if (spaces[*i] == LABEL_CHARS[j])
				break ;
		if (LABEL_CHARS[j] == '\0')
		{
			tasm->error = 3;
			tasm->n_param = 1;
			return (ft_syntax(NULL, tasm, spaces[*i]));
		}
		(*i)++;
	}
	(*i)--;
	return (1);
}

static int		ft_isdir(char *spaces, int *i, t_asm *tasm)
{
	int		isop;

	isop = 0;
	tasm->error = 4;
	if (spaces[++(*i)] == '\0')
		return (ft_syntax(NULL, tasm, spaces[*i]));
	if ((spaces[*i] >= '0' && spaces[*i] <= '9') || spaces[*i] == '+' ||
			spaces[*i] == '-')
		while (spaces[*i] && spaces[*i] != SEPARATOR_CHAR)
		{
			if (spaces[*i] == '+' || spaces[*i] == '-'
					|| (spaces[*i] >= 0 && spaces[*i] <= 9 && isop == 0))
				isop = 1;
			else if (((spaces[*i] == '+' || spaces[*i] == '-') && isop == 1) ||
					spaces[*i] < '0' || spaces[*i] > '9')
			{
				tasm->error = 0;
				tasm->n_param = 1;
				return (ft_syntax(NULL, tasm, spaces[*i]));
			}
			(*i)++;
		}
	if (spaces[*i] != LABEL_CHAR)
		(*i)--;
	return (1);
}

static int		ft_aftersep(int counters[4], char *spaces, t_asm *tasm)
{
	while (spaces[counters[I]] && spaces[counters[I]] != SEPARATOR_CHAR)
	{
		if ((spaces[counters[I]] == DIRECT_CHAR
					&& !(ft_isdir(spaces, counters + I, tasm)))
				|| (spaces[counters[I]] == LABEL_CHAR
					&& !(ft_islab(spaces, counters + I, tasm))))
			return (0);
		else if (spaces[counters[I]] >= '0' && spaces[counters[I]] <= '9')
		{
			while (spaces[counters[I]] && spaces[counters[I]] != SEPARATOR_CHAR)
			{
				if (spaces[counters[I]] < '0' || spaces[counters[I]] > '9')
				{
					tasm->error = 3;
					return (ft_syntax(NULL, tasm, spaces[counters[I]]));
				}
				++(counters[I]);
			}
			--(counters[I]);
		}
		++(counters[I]);
	}
	(counters[I])--;
	return (1);
}

static int		ft_check_separ(char **str, char **spaces, t_asm *tasm,
					int counters[4])
{
	if ((*spaces)[counters[I]] == SEPARATOR_CHAR)
	{
		tasm->n_param++;
		tasm->error = 0;
		counters[NB] = (counters[ISSEP] == 1) ? counters[NB] : counters[NB] - 1;
		counters[RET] = (counters[ISSEP] == 1) ?
			ft_syntax(str, tasm, (*spaces)[counters[I]]) : counters[RET];
		counters[ISSEP] = 1;
	}
	else if ((*spaces)[counters[I]] != SEPARATOR_CHAR)
	{
		counters[ISSEP] = 0;
		if (!(ft_aftersep(counters, *spaces, tasm)))
		{
			ft_strdel(spaces);
			return (0);
		}
	}
	if (counters[NB] < 0 && counters[RET] > 0)
	{
		tasm->error = 1;
		tasm->n_param = 1;
		counters[RET] = (ft_syntax(str, tasm, 0));
	}
	return (1);
}

int				ft_separator(char **str, int nb, t_asm *tasm)
{
	int		counters[4];
	char	*spaces;

	counters[ISSEP] = 0;
	counters[RET] = 1;
	counters[NB] = nb;
	spaces = NULL;
	if (!(spaces = ft_charwtspaces(*str)))
		return (ft_free(NULL, 2, &(tasm->gnl), str));
	counters[I] = -1;
	while (spaces && spaces[++(counters[I])] && counters[RET] != 0)
	{
		if (!(ft_check_separ(str, &spaces, tasm, counters)))
			return (0);
	}
	ft_strdel(&spaces);
	tasm->error = 1;
	tasm->n_param = 1;
	if (counters[NB] != 0 && counters[RET] > 0)
		counters[RET] = ft_syntax(str, tasm, 0);
	return (counters[RET]);
}
