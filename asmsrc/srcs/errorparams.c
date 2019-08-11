/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorparams.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 15:08:58 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/06 10:39:49 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"
#include "../libft/color.h"

static int	ft_istab(t_asm *tasm, int i, int ret)
{
	if (tasm->gnl.line[i] == '\t')
		ret += 8 - (ret % 8);
	else
		ret++;
	return (ret);
}

static void	ft_wrongregister(t_asm *tasm, int occ)
{
	int		i;
	int		ret;

	ft_dprintf(2, "Wrong register at line %i. Min = 1 or Max = %i\n%s%s\n"
			, tasm->gnl.nbline, REG_NUMBER, _RED_, tasm->gnl.line);
	i = 0;
	ret = 0;
	while (tasm->gnl.line[i] && occ)
	{
		if (tasm->gnl.line[i] == SEPARATOR_CHAR)
			occ--;
		ret = ft_istab(tasm, i, ret);
		i++;
	}
	while (tasm->gnl.line[i] && (tasm->gnl.line[i] < '0' ||
				tasm->gnl.line[i] > '9'))
	{
		ret = ft_istab(tasm, i, ret);
		i++;
	}
	ft_dprintf(2, "%s%*c", _GREEN_, ret, '^');
	while (tasm->gnl.line[i] && (tasm->gnl.line[++i] >= '0' &&
				tasm->gnl.line[i] <= '9'))
		ft_dprintf(2, "~");
	ft_dprintf(2, "\n%s", _RESET_);
}

static void	ft_badarg(t_asm *tasm, char *s, int occ)
{
	char	*str;
	int		ret;
	int		i;

	str = ft_strstr(tasm->gnl.line, s);
	ft_dprintf(2, "Bad argument at line %i. Did you mean 'r%s' ?\n%s%s\n",
			tasm->gnl.nbline, s, _RED_, tasm->gnl.line);
	ret = 0;
	i = 0;
	while (tasm->gnl.line[i] && occ)
	{
		if (tasm->gnl.line[i] == SEPARATOR_CHAR)
			occ--;
		ret = ft_istab(tasm, i, ret);
		i++;
	}
	while (tasm->gnl.line[i] && (tasm->gnl.line[i] != s[0]))
	{
		ret = ft_istab(tasm, i, ret);
		i++;
	}
	ft_dprintf(2, "%s%*c\n", _GREEN_, ret, '^');
	ft_dprintf(2, "%*c%s\n", ret, 'r', _RESET_);
}

static void	ft_baddir(t_asm *tasm, int occ, char *s)
{
	int		i;
	int		ret;

	ft_dprintf(2, "Bad argument at line %i. Did you mean '%c%s' ?\n%s%s\n",
			tasm->gnl.nbline, DIRECT_CHAR, s, _RED_, tasm->gnl.line);
	i = 0;
	ret = 0;
	while (tasm->gnl.line[i] && occ)
	{
		if (tasm->gnl.line[i] == SEPARATOR_CHAR)
			occ--;
		ret = ft_istab(tasm, i, ret);
		i++;
	}
	while (tasm->gnl.line[i] && (tasm->gnl.line[i] != s[0]))
	{
		ret = ft_istab(tasm, i, ret);
		i++;
	}
	ft_dprintf(2, "%s%*c\n", _GREEN_, ret, '^');
	ft_dprintf(2, "%*c%s\n", ret, '%', _RESET_);
}

int			ft_errorparams(t_asm *tasm, char *s)
{
	int		occ;

	occ = tasm->n_param - 1;
	if (tasm->error == 4)
		ft_baddir(tasm, occ, s);
	if (tasm->error == 1)
		ft_badarg(tasm, s, occ);
	if (tasm->error == 2)
		ft_wrongregister(tasm, occ);
	ft_strdel(&(tasm->gnl.line));
	return (0);
}
