/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retgnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:29:53 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 14:57:26 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdlib.h>
#include "../includes/asm.h"

static int		ft_validline(t_asm *tasm, int i, int ret)
{
	char	*trim;

	trim = NULL;
	if (!(trim = ft_strtrim(tasm->gnl.line)))
		return (ft_free(NULL, 2, &(tasm->gnl), NULL));
	if (i == 1 && trim[0] != '\0' && trim[0] != COMMENT_CHAR &&
			trim[0] != ';' && trim[0] != '.')
	{
		ft_strdel(&trim);
		return (-1);
	}
	if ((i == 1 && trim[0] == '.') || i == 0)
	{
		ft_strdel(&trim);
		return (ret);
	}
	ft_strdel(&trim);
	return (-2);
}

int				ft_retgnl(t_asm *tasm, int i)
{
	int		ret;
	int		nbline;
	int		valid;

	if (i == 1)
		nbline = tasm->gnl.nbline;
	ft_strdel(&(tasm->gnl.line));
	ret = 0;
	while ((ret = ft_gnl(tasm->file.fdopen, &(tasm->gnl.line))) > 0)
	{
		tasm->gnl.nbline++;
		if (tasm->gnl.line)
		{
			valid = ft_validline(tasm, i, ret);
			if (valid >= 0)
				return (valid);
			else if (valid == -1)
				break ;
		}
		ft_strdel(&(tasm->gnl.line));
	}
	if (i == 1)
		tasm->gnl.nbline = nbline + 1;
	ft_strdel(&(tasm->gnl.line));
	return (0);
}
