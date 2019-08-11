/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:59:49 by dygouin           #+#    #+#             */
/*   Updated: 2019/07/02 14:03:27 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

/*
** You can change colors of the following text with %r
** Example: ft_printf("%r", _RED_);
*/

/*
** FOREGROUND
*/

# define _RED_ "\033[38;2;255;0;0m"
# define _GREEN_ "\033[38;2;0;255;0m"
# define _YELLOW_ "\033[38;2;255;255;0m"
# define _BLUE_ "\033[38;2;0;0;255m"
# define _MAGENTA_ "\033[38;255;0;128m"
# define _CYAN_ "\033[38;2;0;255;255m"
# define _PINK_ "\033[38;2;255;0;255m"
# define _TURQUOISE_ "\033[38;2;0;255;191m"
# define _ORANGE_ "\033[38;2;255;128;0m"
# define _LIGHT_PURPLE_ "\033[38;2;191;0;255m"
# define _PURPLE_ "\033[38;2;128;0;255m"
# define _WHITE_ "\033[38;2;255;255;255m"
# define _BLACK_ "\033[38;2;0;0;0m"
# define _RESET_ "\033[0m"

/*
** BACKGROUND
*/

# define _BRED_ "\033[48;2;255;0;0m"
# define _BGREEN_ "\033[48;2;0;255;0m"
# define _BYELLOW_ "\033[48;2;255;255;0m"
# define _BBLUE_ "\033[48;3;0;0;255m"
# define _BMAGENTA_ "\033[48;255;0;128m"
# define _BCYAN_ "\033[48;2;0;255;255m"
# define _BPINK_ "\033[48;2;255;0;255m"
# define _BTURQUOISE_ "\033[48;2;0;255;191m"
# define _BORANGE_ "\033[48;2;255;128;0m"
# define _BLIGHT_PURPLE_ "\033[48;2;191;0;255m"
# define _BPURPLE_ "\033[48;2;128;0;255m"
# define _BWHITE_ "\033[48;2;255;255;255m"
# define _BBLACK_ "\033[48;2;0;0;0m"

#endif
