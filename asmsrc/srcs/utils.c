/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 14:43:52 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 14:46:39 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"

int			ft_retmulterr(char **str, char **trim, char ***split)
{
	ft_strdel(str);
	ft_strdel(trim);
	ft_free_tab2d(split);
	return (0);
}

int			ft_strok(char **trim, t_asm *tasm, t_gnl *gnl, int nbline)
{
	char	**split;
	int		len;
	int		lensplit;

	split = NULL;
	len = 0;
	lensplit = 0;
	if (!(split = ft_splitwhitespaces(*trim)))
		return (ft_free(&split, 2, &(tasm->gnl), trim));
	while (split[lensplit])
		lensplit++;
	len = ft_strlen(split[lensplit - 1]);
	if ((split)[1][0] != '\"' || (split)[lensplit - 1][len - 1] != '\"')
	{
		gnl->nbline = nbline;
		ft_strdel(trim);
		return (ft_freecom(&split, 4, NULL, gnl));
	}
	ft_free_tab2d(&split);
	return (1);
}
