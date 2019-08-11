/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:52:06 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 14:41:17 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <stdlib.h>
#include "../includes/asm.h"

int			start(char **av, t_file *file, int i)
{
	if (!(file->name = ft_recupfile(av[i])))
	{
		ft_dprintf(2, "File is not .s\n");
		return (0);
	}
	if ((file->fdopen = open(av[i], O_RDONLY)) == -1)
	{
		ft_strdel(&(file->name));
		ft_dprintf(2, "Open() failed\n");
		return (0);
	}
	return (1);
}

static char	*ft_errfree(char **rname, char **ext)
{
	ft_free(NULL, 2, NULL, NULL);
	ft_strdel(rname);
	ft_strdel(ext);
	return (NULL);
}

char		*ft_recupfile(char *name)
{
	char	*chr;
	char	*rname;
	char	*join;
	char	*ext;

	rname = NULL;
	ext = NULL;
	chr = NULL;
	join = NULL;
	chr = ft_strrchr(name, '.');
	if (!chr)
		return (NULL);
	if (ft_strcmp(chr, ".s"))
		return (NULL);
	if (!(rname = (char*)malloc(sizeof(char) * (chr - name + 1))))
		return (ft_errfree(NULL, NULL));
	ft_strncpy(rname, name, chr - name);
	if (!(ext = ft_strdup(".cor")))
		return (ft_errfree(&rname, NULL));
	if (!(join = ft_strjoinfree(rname, ext)))
		return (ft_errfree(&rname, &ext));
	return (join);
}

int			createfile(char *name)
{
	int		fd;

	if ((fd = open(name, O_CREAT | O_TRUNC | O_RDWR, 00755)) == -1)
		return (-1);
	if (fd != -1)
	{
		if ((fd = open(name, O_RDWR)) == -1)
			return (-1);
	}
	return (fd);
}

int			ft_closeall(t_asm tasm)
{
	if (tasm.file.fdopen >= 0)
	{
		if ((close(tasm.file.fdopen)) == -1)
		{
			ft_dprintf(2, "Close() failed\n");
			return (-1);
		}
	}
	if (tasm.file.fdwrite >= 0)
	{
		if ((close(tasm.file.fdwrite)) == -1)
		{
			ft_dprintf(2, "Close() failed\n");
			return (-1);
		}
	}
	return (1);
}
