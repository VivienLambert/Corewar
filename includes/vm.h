/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:23:18 by vlambert          #+#    #+#             */
/*   Updated: 2019/06/26 10:44:46 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../includes/op.h"
# include "../includes/errors.h"

typedef struct		s_proc
{
	struct s_proc	*next;
	int				number;
	int				period_lives;
	unsigned int	pc;
	int				waiting;
}					t_proc;

typedef struct		s_player
{
	int				number;
	int				period_lives;
	int				last_p_lives;
	int				last_live;
	int				carry;
	unsigned int	size;
	char			name[PROG_NAME_LENGTH + 4];
	char			comment[COMMENT_LENGTH + 4];
	unsigned char	code[CHAMP_MAX_SIZE + 1];
	unsigned char	registers[REG_NUMBER][REG_SIZE];
	t_proc			*proc;
}					t_player;

typedef struct		s_vm
{
	unsigned char	mem[MEM_SIZE];
	t_player		players[MAX_PLAYERS];
	int				player_turn;
	int				cycles;
	int				cycle_to_die;
	int				cycles_limit;
	int				process;
	int				options;
	int				players_nbr;
	char			err[ERR_TYPE_NBR][ERR_MSG_SIZE];
}					t_vm;

int					options(int ac, char *av[], t_vm *vm);
int					read_champ(char *champ, t_vm *vm);

/*
**  Set errors messages and error code to 0
**  Add a new error message by adding :
**  	ft_strcpy(vm->err[ERR_XXXXXX], "Your message"); 
**	in errors.c following function.
**	Your message must respect ERR_MSG_SIZE size and refer to errors.h
*/
void    init_err(t_vm *vm, int *err);

#endif
