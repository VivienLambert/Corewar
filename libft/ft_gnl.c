/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 12:17:20 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/19 12:46:58 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

int		ft_concat(char to_read[BUFF_SIZE + 1], char **buffer)
{
	char *to_free;

	if (!(*buffer))
		*buffer = ft_strdup(to_read);
	else
	{
		to_free = *buffer;
		if (!(*buffer = ft_strjoin(*buffer, to_read)))
		{
			free(to_free);
			return (0);
		}
		free(to_free);
	}
	return (1);
}

char	*ft_read(char to_read[BUFF_SIZE + 1], char **buffer, int fd)
{
	int		ret;

	*buffer = 0;
	ret = 1;
	if (to_read[0] && !ft_concat(to_read, buffer))
		return (NULL);
	while (!(ft_strchr(to_read, '\n')))
	{
		ret = read(fd, to_read, BUFF_SIZE);
		if ((ret && !(to_read[0])) || ret == -1)
		{
			ft_strdel(buffer);
			return (NULL);
		}
		to_read[ret] = 0;
		if (!ft_concat(to_read, buffer))
			return (NULL);
		if (ret == 0)
			break ;
	}
	return (*buffer);
}

char	*ft_copy(char to_read[BUFF_SIZE + 1], char *buffer)
{
	size_t	size;
	size_t	j;
	char	*new;

	size = 0;
	j = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	if (!(new = ft_strnew(size)))
		return (NULL);
	while (j < size || j == 0)
	{
		new[j] = buffer[j];
		j++;
	}
	j = 0;
	while (buffer[size] || j == 0)
	{
		if (buffer[size])
			size++;
		to_read[j++] = buffer[size];
	}
	free(buffer);
	return (new);
}

int		ft_gnl(const int fd, char **line)
{
	static char		to_read[BUFF_SIZE + 1];
	char			*buffer;

	if (fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (!ft_read(to_read, &buffer, fd))
		return (-1);
	if (!(*line = ft_copy(to_read, buffer)))
		return (-1);
	if (*line[0])
	{
		if (*line[0] == '\n')
		{
			*line[0] = '\0';
			return (1);
		}
		return (ft_strlen(*line));
	}
	ft_strdel(line);
	return (0);
}
