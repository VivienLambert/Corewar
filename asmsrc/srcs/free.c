/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 13:32:57 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/29 14:28:07 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/color.h"
#include <errno.h>
#include <stdio.h>

void		ft_free_all(char ***tab, char **str)
{
	if (str && *str)
		ft_strdel(str);
	if (tab && *tab)
		ft_free_tab2d(tab);
}

static void	ft_empty(char **str, char ***tab, t_gnl *gnl)
{
	int		i;

	i = 0;
	ft_free_all(tab, str);
	ft_dprintf(2, "Empty command at line %i\n%s%s\n", gnl->nbline,
			_RED_, gnl->line);
	i = 0;
	while (gnl->line[i] != '.')
		i++;
	ft_dprintf(2, "%s%*c%s\n", _GREEN_, ft_strclentab(gnl->line, 0,
				&gnl->line[i], 0),
			'^', _RESET_);
}

static void	ft_unexp_comment(char ***tab, char **str, t_gnl *gnl)
{
	int i;
	int	tot;
	int	cal;

	i = -1;
	tot = 0;
	while (gnl->line[++i])
	{
		if (gnl->line[i] == '\t')
		{
			cal = 8 - (tot % 8);
			tot += cal;
		}
		else
			tot++;
		if (gnl->line[i] == '.')
			break ;
	}
	ft_dprintf(2, "comment is unexpected at line %i. Error at name.\
			\n%s%s\n%s%*c%s\n",
			gnl->nbline, _RED_, gnl->line, _GREEN_, tot, '^', _RESET_);
	ft_free_all(tab, str);
}

int			ft_free(char ***tab, int err, t_gnl *gnl, char **str)
{
	if (err == 1)
		ft_dprintf(2, "Champion name too long (Max length %i)\n%sThe name \
has %i characters\n%s", PROG_NAME_LENGTH, _RED_, ft_strlen((*tab)[1]), _RESET_);
	if (err == 2)
		perror("asm");
	if (err == 3)
		ft_dprintf(2, "Comment too long (Max length %i)\n%sYour comment \
has %i characters\n%s", COMMENT_LENGTH, _RED_, ft_strlen((*tab)[1]), _RESET_);
	if (err == 4)
		ft_dprintf(2, "Champion too long. End of file at line %i\n",
				gnl ? gnl->nbline : -1);
	if (err == 5)
		ft_unexp_comment(tab, str, gnl);
	if (err == 0)
		ft_empty(str, tab, gnl);
	else if (err <= 3 && err > 0)
		ft_free_all(tab, str);
	if (gnl)
		ft_strdel(&(gnl->line));
	return (0);
}
