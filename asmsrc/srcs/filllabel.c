/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filllabel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:04:56 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/06 15:05:10 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

static int		ft_verifint(char *split, t_asm *tasm)
{
	int		i;
	int		isop;

	i = -1;
	isop = 0;
	if (!split)
	{
		tasm->error = 3;
		return (ft_syntax(NULL, tasm, ' '));
	}
	while (split[++i])
	{
		if (split[i] == '+' || split[i] == '-' || (split[i] >= 0 &&
				split[i] <= 9))
			isop = 1;
		else if (((split[i] == '+' || split[i] == '-') && isop == 1) ||
				split[i] < '0' || split[i] > '9')
		{
			tasm->error = 3;
			return (ft_syntax(NULL, tasm, split[i]));
		}
	}
	return (1);
}

static int		ft_retparam(t_op *tmp, int addr, int filladdr)
{
	unsigned short	stmp;
	unsigned int	iparam;

	if (accept_d4(tmp->inst))
	{
		iparam = addr - filladdr;
		return (iparam);
	}
	else
	{
		stmp = (addr - filladdr);
		if (addr >= 0)
			return (stmp);
	}
	return (0);
}

static int		ft_paramlabel(t_op *op, char *label, int nparam)
{
	t_op			*tmp;
	int				addr;
	int				filladdr;

	tmp = op;
	addr = -1;
	filladdr = 0;
	while (tmp->next)
	{
		filladdr += tmp->size;
		if (tmp->label)
			if (!ft_strcmp(tmp->label, label))
				addr = tmp->addr;
		tmp = tmp->next;
	}
	if (addr == -1)
	{
		if (!(tmp->searchlabel[nparam - 1] = ft_strdup(label)))
			return (ft_free(NULL, 2, NULL, NULL));
	}
	else
		tmp->searchlabel[nparam - 1] = NULL;
	return (ft_retparam(tmp, addr, filladdr));
}

static int		ft_dirchar(t_asm *tasm, char **split, char ***label)
{
	char	**dirsplit;
	int		param;

	dirsplit = NULL;
	param = 0;
	if (!(dirsplit = ft_strsplit(split[tasm->n_param], DIRECT_CHAR)))
	{
		tasm->error = 1;
		return (ft_free(label, 2, &tasm->gnl, NULL));
	}
	if (!(ft_verifint(dirsplit[0], tasm)))
	{
		tasm->error = 1;
		ft_free_tab2d(&dirsplit);
		return (0);
	}
	param = ft_atui(dirsplit[0]);
	ft_free_tab2d(&dirsplit);
	return (param);
}

unsigned int	ft_filllabel(t_asm *tasm, char **split)
{
	unsigned int	param;
	char			**label;

	label = NULL;
	tasm->error = 0;
	if (split[tasm->n_param] && split[tasm->n_param][1] == LABEL_CHAR)
	{
		if (!(label = ft_strsplit(split[tasm->n_param], LABEL_CHAR)))
			return (!(tasm->error = !ft_free(NULL, 2, &tasm->gnl, NULL)));
		param = ft_paramlabel(tasm->op, label[1], tasm->n_param);
	}
	else if (split[tasm->n_param][0] == DIRECT_CHAR)
	{
		param = ft_dirchar(tasm, split, &label);
		if (tasm->error == 1)
			return (0);
	}
	else
	{
		if (!(label = ft_strsplit(split[tasm->n_param], LABEL_CHAR)))
			return (!(tasm->error = !ft_free(NULL, 2, &tasm->gnl, NULL)));
		param = ft_paramlabel(tasm->op, label[0], tasm->n_param);
	}
	ft_free_tab2d(&label);
	return (param);
}
