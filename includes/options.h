/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:06:17 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/06 15:37:46 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

/*
**  Authorized options :
**
**  OPTV (-v):      Verbose
**  OPTD (-d):      Debug
**  OPTMAJV (-V):   Visual
*/

# define OPTV 1
# define OPTD 1<<1
# define OPTMAJV 1<<2
# define OPTZ 1<<3

#endif
