/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:56:54 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/06 16:17:25 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"
#include <stdlib.h>

static int	veriflabel(char *split)
{
	int		i;
	int		j;
	int		ok;

	i = -1;
	while (split[++i])
	{
		j = -1;
		ok = 0;
		while (LABEL_CHARS[++j])
			if (split[i] == LABEL_CHARS[j])
				ok = 1;
		if (ok == 0)
			return (0);
	}
	return (1);
}

static void	ft_supprlab(char *trim, char **split)
{
	int		lensplit;
	int		len;
	int		i;

	if (!split[0])
		return ;
	lensplit = ft_strlen(split[0]) + 1;
	len = ft_strlen(trim);
	i = 0;
	while (trim[lensplit])
	{
		trim[i] = trim[lensplit];
		lensplit++;
		i++;
	}
	trim[i] = '\0';
}

static int	ft_onelab(char **trim, int ret, t_gnl *gnl, t_op *new)
{
	char	**split;
	int		verif;

	split = NULL;
	if (!(split = ft_strsplit(*trim, ':')))
		return (ft_free(&split, 2, gnl, NULL));
	if (ret > 0)
	{
		if (!(verif = veriflabel(split[0])))
			ret = ft_freecom(NULL, 3, split[0], gnl);
		if (split[0] && verif != 2)
		{
			ft_supprlab(*trim, split);
			if (!(new->label = ft_strdup(split[0])))
				return (ft_free(&split, 2, gnl, NULL));
			new->line = gnl->nbline;
		}
	}
	ft_free_tab2d(&split);
	return (ret);
}

int			ft_label(char *trim, t_gnl *gnl, t_op *new)
{
	int		i;
	int		labchar;
	int		ret;

	i = -1;
	labchar = 0;
	ret = 1;
	while (trim[++i] && ((trim[i] < 9 || trim[i] > 13) && trim[i] != 32))
		if (trim[i] == LABEL_CHAR)
			labchar++;
	if (labchar == 0)
		ret = -1;
	else if (labchar > 1)
		ret = ft_freecom(NULL, 3, trim, gnl);
	else if (labchar == 1)
	{
		if (!(ft_onelab(&trim, ret, gnl, new)))
			return (0);
	}
	return (ret);
}
