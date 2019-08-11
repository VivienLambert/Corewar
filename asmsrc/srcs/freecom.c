/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freecom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:24:29 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 15:22:06 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/color.h"

static void	ft_notstring2(t_gnl *gnl, int counters[5])
{
	while (gnl->line[counters[I]])
	{
		if (gnl->line[(counters[I])++] == '\t')
		{
			counters[J] = 8 - (counters[RET] % 8);
			counters[RET] += counters[J];
			while (counters[J]-- > 0)
				ft_dprintf(2, "~");
		}
		else
		{
			(counters[RET])++;
			ft_dprintf(2, "~");
		}
	}
	if (gnl->line[counters[TMPI]] != '\"')
	{
		ft_dprintf(2, "\n%*c\n%s", counters[TMPRET], '\"', _RESET_);
	}
	else
	{
		ft_dprintf(2, "~");
		ft_dprintf(2, "%c\n%*c\n%s", '^', counters[RET] + 1, '\"', _RESET_);
	}
}

static void	ft_notstring(char ***tab, char *str, t_gnl *gnl)
{
	int		counters[5];

	counters[RET] = 0;
	counters[I] = 0;
	ft_dprintf(2, "%s is not a string, line %i\n%s%s%s\n", str, gnl->nbline,
			_RED_, gnl->line, _GREEN_);
	while (gnl->line[counters[I]] != (*tab)[0][0])
		counters[RET] = ft_passtab(gnl->line, counters + I, counters[RET]);
	counters[J] = -1;
	while (gnl->line[(counters[I])++] == (*tab)[0][++(counters[J])])
		(counters[RET])++;
	while (gnl->line[(counters[I])] == ' ' || gnl->line[(counters[I])] == '\t')
		counters[RET] = ft_passtab(gnl->line, counters + I, counters[RET]);
	(counters[RET])++;
	counters[TMPRET] = counters[RET];
	counters[TMPI] = counters[I];
	if (gnl->line[counters[I]] == '\"')
		ft_dprintf(2, "%*c", (counters[RET])++, ' ');
	else
		ft_dprintf(2, "%*c", counters[RET], '^');
	ft_notstring2(gnl, counters);
}

static void	ft_syntax_msg(t_gnl *gnl)
{
	int		i;
	int		j;

	i = 0;
	ft_dprintf(2, "Syntax Error at line %i\n%s%s\n%s", gnl->nbline, _RED_,
				gnl->line, _GREEN_);
	while (gnl->line[i++])
	{
		j = -1;
		if (gnl->line[i] != ' ' && gnl->line[i] != '\t')
		{
			while (LABEL_CHARS[++j])
				if (LABEL_CHARS[j] == gnl->line[i])
					break ;
			if (LABEL_CHARS[j] == '\0')
				break ;
		}
	}
	ft_dprintf(2, "%*c%s\n",
		ft_strclentab(gnl->line, '~', &(gnl->line[i]), 0), '^', _RESET_);
}

int			ft_freecom(char ***tab, int err, char *str, t_gnl *gnl)
{
	char	*s;

	if (err == 0)
	{
		s = ft_strstr(gnl->line, str);
		ft_dprintf(2, "Command '%s' invalid at line %i\n", *(tab)[0],
				gnl->nbline);
		ft_dprintf(2, "%s%s\n%s", _RED_, gnl->line, _GREEN_);
		ft_strprintspaces(gnl->line);
		ft_dprintf(2, "%*c%s\n", ft_diffis(str, *(tab)[0]) + 1, '^', _RESET_);
	}
	if (err == 1)
		ft_notstring(tab, str, gnl);
	if (err == 3)
		ft_syntax_msg(gnl);
	if (err == 4)
		ft_dprintf(2, "Command '%s' invalid at line %i\n", (*tab)[0],
				gnl->nbline);
	ft_free_tab2d(tab);
	ft_strdel(&(gnl->line));
	return (0);
}
