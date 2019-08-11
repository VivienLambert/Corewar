/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searchlabel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 11:39:35 by ayguillo          #+#    #+#             */
/*   Updated: 2019/07/22 18:14:34 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"
#include "../libft/color.h"

static int	ft_searchlabel1(t_op **op, t_op *search, int i, int err)
{
	t_op	*tmp;

	tmp = *op;
	while (tmp)
	{
		if (tmp->label)
		{
			if (!(ft_strcmp(search->searchlabel[i], tmp->label)))
			{
				search->param[i] = (MEM_SIZE -
						(search->addr - tmp->addr + MEM_SIZE) % MEM_SIZE);
				ft_strdel(&(search->searchlabel[i]));
				break ;
			}
		}
		tmp = tmp->next;
	}
	if (err == 1 && !(tmp))
		return (0);
	return (1);
}

int			ft_searchlabel(t_asm *tasm, int err)
{
	t_op	*tmp;
	int		i;

	tmp = tasm->op;
	while (tmp)
	{
		i = 0;
		while (i < 3)
		{
			if (tmp->searchlabel[i])
			{
				if (!(ft_searchlabel1(&tasm->op, tmp, i, err)))
				{
					ft_dprintf(2, "%slabel '%s' at line %i undeclared.%s\n",
							_RED_, tmp->searchlabel[i], tmp->line, _RESET_);
					return (0);
				}
			}
			++i;
		}
		if (tmp->addr > CHAMP_MAX_SIZE)
			return (ft_free(NULL, 4, &tasm->gnl, NULL));
		tmp = tmp->next;
	}
	return (1);
}
