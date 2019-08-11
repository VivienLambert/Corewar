/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:11:17 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 15:14:23 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"
#include <stdlib.h>

static int	ft_recupinst(t_asm *tasm, char **trim)
{
	t_op	*tmp;
	t_op	*new;

	tmp = tasm->op;
	if (!(*trim[0]))
		ft_strdel(trim);
	if (!(*trim))
		return (1);
	if (!(new = ft_memalloc(sizeof(t_op))))
		return (ft_free(NULL, 2, &(tasm->gnl), trim));
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		tasm->op = new;
	if (!(ft_label(*trim, &(tasm->gnl), new)))
	{
		ft_strdel(trim);
		return (0);
	}
	ft_fillparam1(tasm, 0, 0, 0);
	return (!(ft_instructions(trim, tasm)) ? 0 : 1);
}

int			ft_readinst(t_asm *tasm)
{
	char	*trim;
	int		i;

	trim = NULL;
	while ((ft_retgnl(tasm, 0)) > 0)
	{
		ft_strdel(&trim);
		if (tasm->gnl.line && (i = -1))
		{
			if (!(trim = ft_strtrim(tasm->gnl.line)))
				return (ft_free(NULL, 2, &(tasm->gnl), NULL));
			while (trim[++i])
				if (trim[i] == COMMENT_CHAR || trim[i] == ';')
					trim[i] = '\0';
			if ((ft_recupinst(tasm, &trim)) <= 0)
			{
				ft_strdel(&trim);
				ft_strdel(&(tasm->gnl.line));
				return (0);
			}
		}
		ft_strdel(&(tasm->gnl.line));
	}
	ft_strdel(&trim);
	return (1);
}
