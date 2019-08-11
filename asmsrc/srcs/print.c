/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:34:23 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 15:11:57 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../libft/libft.h"
#include "../includes/asm.h"

int			ft_nbquote(char *str)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (str[++i])
		if (str[i] == '\"')
			ret++;
	return (ret);
}

char		*ft_strjoinfree1(char *s1, char *s2)
{
	char *s3;
	char *s4;

	if (!s1 || !s2)
		return (NULL);
	if (!(s3 = ft_strjoin(s1, "\n")))
		return (NULL);
	if (s1)
		ft_strdel(&s1);
	if (!(s4 = ft_strjoin(s3, s2)))
		return (NULL);
	if (s3)
		ft_strdel(&s3);
	return (s4);
}

static int	readerror(t_asm *tasm)
{
	ft_dprintf(2, "Read() failed, syntax invalid or empty command at line %i\n"
			, tasm->gnl.nbline);
	ft_strdel(&(tasm->gnl.line));
	return (0);
}

int			printfile(t_header *header, t_asm *tasm)
{
	int		lenname;
	int		lencom;
	t_op	*tmp;

	if (((ft_retgnl(tasm, 1)) <= 0 && !(readerror(tasm)))
		|| ft_recup(header, tasm, &lenname, NAME) <= 0
			|| ((ft_retgnl(tasm, 1)) <= 0 && !(readerror(tasm)))
		|| ft_recup(header, tasm, &lencom, COM) <= 0
		|| !(ft_readinst(tasm)))
		return (0);
	tmp = tasm->op;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
	{
		ft_dprintf(2, "No instruction\n");
		return (0);
	}
	header->prog_size = ft_reversebyte(tmp->addr + tmp->size, 4);
	header->magic = ft_reversebyte(COREWAR_EXEC_MAGIC, 4);
	return (1);
}
