/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 12:59:06 by ayguillo          #+#    #+#             */
/*   Updated: 2019/09/10 13:01:19 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../libft/color.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../includes/asm.h"

void		ft_dellstop(t_asm *tasm)
{
	t_op	*tmp1;
	t_op	*tmp2;
	int		i;

	tmp1 = tasm->op;
	ft_strdel(&(tasm->gnl.line));
	while (tmp1)
	{
		i = -1;
		tmp2 = tmp1->next;
		while (++i < 3)
			ft_strdel(&tmp1->searchlabel[i]);
		ft_strdel(&tmp1->label);
		free(tmp1);
		tmp1 = NULL;
		tmp1 = tmp2;
	}
}

static int	ft_corfile(t_asm tasm, t_header header)
{
	if (((tasm.file.fdwrite = createfile(tasm.file.name)) == -1))
	{
		while ((ft_gnl(tasm.file.fdopen, &(tasm.gnl.line))) > 0)
			ft_strdel(&(tasm.gnl.line));
		ft_closeall(tasm);
		ft_strdel(&(tasm.file.name));
		ft_dellstop(&tasm);
		ft_dprintf(2, "Open() failed\n");
		return (-1);
	}
	if (ft_searchlabel(&tasm, 1))
	{
		write(tasm.file.fdwrite, &header, sizeof(t_header));
		write_code(&(tasm.file), tasm.op);
		ft_printf("%sWriting output program to %s%s\n",
				_GREEN_, tasm.file.name, _RESET_);
	}
	return (1);
}

void		ft_init(t_asm *tasm, t_header *header)
{
	ft_bzero(header, sizeof(*header));
	ft_bzero(tasm, sizeof(*tasm));
	tasm->file.fdopen = -1;
	tasm->file.fdwrite = -1;
	ft_bzero(tasm, sizeof(tasm->op));
}

int			multifile(char **av, int i)
{
	t_header	header;
	t_asm		tasm;

	ft_init(&tasm, &header);
	ft_printf("Compiling %s . . .\n", av[i]);
	if (!(start(av, &(tasm.file), i)))
		return (-1);
	if (!(printfile(&header, &tasm)))
	{
		while ((ft_gnl(tasm.file.fdopen, &(tasm.gnl.line))) > 0)
			ft_strdel(&(tasm.gnl.line));
		ft_closeall(tasm);
		ft_strdel(&(tasm.file.name));
		ft_dellstop(&tasm);
		return (-1);
	}
	if ((ft_corfile(tasm, header)) == -1)
		return (-1);
	while ((ft_gnl(tasm.file.fdopen, &(tasm.gnl.line))) > 0)
		ft_strdel(&(tasm.gnl.line));
	ft_closeall(tasm);
	ft_strdel(&(tasm.file.name));
	ft_dellstop(&tasm);
	return (0);
}

int			main(int ac, char **av)
{
	int				i;
	int				ret;

	i = 0;
	ret = 0;
	if (ac == 1)
	{
		ft_dprintf(2, "Usage : ./asm [files .s]\n");
		return (0);
	}
	while (++i < ac)
		ret = multifile(av, i);
	return (ret);
}
