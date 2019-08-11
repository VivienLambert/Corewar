/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 10:14:28 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/09 10:22:11 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strreplace(char *src, char to_find, char replace_by)
{
	while (*src && to_find)
	{
		if (*src == to_find)
			*src = replace_by;
		src++;
	}
}
