/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nameandcom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 13:21:38 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 15:23:01 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/asm.h"

static int	ft_errormulti(char **str, char ***split, int line, t_gnl *gnl)
{
	ft_dprintf(2, "%s is invalid at line %i\n", *split[0], line);
	ft_strdel(str);
	ft_free_tab2d(split);
	return (ft_free(NULL, 6, gnl, NULL));
}

static int	ft_quote(t_asm *tasm, char **str, char **trim, char ***split)
{
	t_gnl	*gnl;
	int		line;

	gnl = &(tasm->gnl);
	line = gnl->nbline;
	if (!(*str = ft_strjoinfree1(*str, gnl->line)))
	{
		ft_strdel(str);
		return (ft_free(split, 2, gnl, trim));
	}
	if ((ft_nbquote(gnl->line)) > 0
			|| ft_strstr((gnl->line), COMMENT_CMD_STRING))
	{
		if (ft_strstr((gnl->line), COMMENT_CMD_STRING))
		{
			ft_strdel(str);
			return (ft_free(split, 5, gnl, trim));
		}
		return (-1);
	}
	return (1);
}

static int	ft_multiname(t_asm *tasm, char **trim, char ***split)
{
	char	*str;
	t_gnl	*gnl;
	int		line;
	int		r;

	gnl = &(tasm->gnl);
	line = gnl->nbline;
	if (!(str = ft_strdup(*trim)))
		return (ft_free(split, 2, gnl, trim));
	while (ft_retgnl(tasm, 0) && (r = ft_quote(tasm, &str, trim, split)) > 0)
		;
	if (r == 0)
		return (ft_retmulterr(&str, trim, split));
	if (ft_nbquote(str) != 2)
		return (ft_errormulti(&str, split, line, gnl));
	ft_strdel(trim);
	*trim = ft_strtrim(str);
	if (!(ft_strok(trim, tasm, gnl, line)))
		return (ft_retmulterr(&str, NULL, split));
	ft_strdel(&str);
	return (1);
}

static int	ft_multicom(t_asm *tasm, char **trim, char ***split)
{
	char	*str;
	int		line;

	line = tasm->gnl.nbline;
	if (!(str = ft_strdup(*trim)))
		return (ft_free(split, 2, &(tasm->gnl), trim));
	while ((ft_retgnl(tasm, 0)))
	{
		if (!(str = ft_strjoinfree1(str, tasm->gnl.line)))
		{
			ft_strdel(&str);
			return (ft_free(split, 2, &(tasm->gnl), trim));
		}
		if (ft_nbquote(tasm->gnl.line) > 0)
			break ;
	}
	ft_strdel(trim);
	if (ft_nbquote(str) != 2)
		return (ft_errormulti(&str, split, line, &(tasm->gnl)));
	*trim = ft_strtrim(str);
	if (!(ft_strok(trim, tasm, &(tasm->gnl), line)))
		return (ft_retmulterr(&str, NULL, split));
	ft_strdel(&str);
	return (1);
}

int			ft_multiline(t_asm *tasm, char **trim, char ***split)
{
	if (!(ft_strcmp((*split)[0], NAME_CMD_STRING)))
		return (ft_multiname(tasm, trim, split));
	if (!(ft_strcmp((*split)[0], COMMENT_CMD_STRING)))
		return (ft_multicom(tasm, trim, split));
	return (1);
}
