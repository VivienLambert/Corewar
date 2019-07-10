/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 18:07:44 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/10 15:59:48 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_STRUCT_H
# define VM_STRUCT_H

# include <curses.h>
# include "op.h"
# include "errors.h"

/*
** NCURSES VISUALIZER
*/

typedef struct	s_win
{
	WINDOW		*win;
	int			x;
	int			y;
	int			width;
	int			height;
}				t_win;

typedef struct		s_display
{
	t_win			memory;
}					t_display;

/*
** VM
*/

typedef struct		s_proc
{
	struct s_proc	*next;
	unsigned int	pc;
	unsigned int	number;
	int				period_lives;
	int				waiting;
	int				carry;
	int				regs[REG_NUMBER];
	int				player;
	int				dir_size;
}					t_proc;

typedef struct		s_player
{
	int				number;
	int				period_lives;
	int				last_p_lives;
	int				alive_proc;
	unsigned int	size;
	char			color[20];
	char			name[PROG_NAME_LENGTH + 4];
	char			comment[COMMENT_LENGTH + 4];
	unsigned char	code[CHAMP_MAX_SIZE + 1];
}					t_player;

typedef struct		s_vm
{
	unsigned char	mem[MEM_SIZE];
	char			mem_infos_code[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	t_proc			*proc;
	int				last_player_alive;
	int				cycles;
	int				cycles_limit;
	int				period_cycles;
	int				cycle_to_die;
	int				checks;
	int				period_lives;
	int				options;
	int				players_nbr;
	char			err[ERR_TYPE_NBR][ERR_MSG_SIZE];
	t_display		display;
}					t_vm;

/*
** PROCESSES/INSTRUCTIONS
*/

typedef struct		s_param
{
	int				type;
	int				val;
}					t_param;

#endif
