/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 10:01:45 by ayguillo          #+#    #+#             */
/*   Updated: 2019/08/07 10:05:25 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROC_H
# define PROC_H

# include <stdbool.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "vm_structs.h"
# include "display.h"

# define T_SDIR 2
# define T_LDIR 4
# define ERROR -1
# define NO_ERROR 0
# define T_OPCODE 1
# define T_OCP 1
# define GLOBAL_DBG 0
# define VISU_ON 0

/*
** MAIN
*/

int				placeholder_init_data(t_vm *vm, t_proc *process);
int				process_execute(t_vm *vm, t_proc *process);

/*
** DEBUG
*/

void			tmp_print_mem(unsigned char *mem, unsigned int size);
void			local_dbg(bool debug, const char *fmt_msg, ...);
void			dbg_print_proc_head(bool debug, t_vm *vm, t_proc *process);
void			dbg_print_proc_end(bool debug, t_vm *vm, t_proc *process);
void			dbg_print_params_head(bool debug);
void			dbg_print_instruction_head(bool debug, char *op);
void			dbg_print_ind_load(bool debug, char *msg,
					unsigned int addr, unsigned int load);
void			dbg_print_dir_load(bool debug, char *msg, unsigned int load);
void			dbg_print_math(bool debug, char op, unsigned int p1,
					unsigned int p2, unsigned int result);
void			dbg_print_addr(bool debug, t_op op, t_proc *proc,
					unsigned int p1, unsigned int p2);

/*
** INSTRUCTIONS
*/

void			op_live(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_ld(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_st(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_add(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_sub(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_and(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_or(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_xor(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_jmpz(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_ldi(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_sti(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_fork(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_lld(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_lldi(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_lfork(t_vm *vm, t_proc *process, t_param *params, t_op op);
void			op_aff(t_vm *vm, t_proc *process, t_param *params, t_op op);

/*
** INSTRUCTION TOOLS
*/

int				get_op_parameters(t_vm *vm, t_proc *pr, t_param *params,
					t_op op);
unsigned int	read_parameter(t_vm *vm, t_proc *proc, t_op op, t_param *param);
unsigned int	calculate_address(t_proc *proc, t_op op, unsigned int p1,
					unsigned int p2);

/*
** READ FROM VM/PROCESS
*/

unsigned int	read_from_register(t_proc *proc, int id);
unsigned char	read_byte_from_vm(t_vm *vm, int address);
int				read_from_vm(t_vm *vm, int address, int read_size);

/*
** WRITE TO VM/PROCESS
*/

void			write_to_register(t_proc *process, int register_id, int write);
void			write_byte_to_vm(t_vm *vm, unsigned int address, char byte);
void			write_to_vm(t_vm *vm, int address, int write, int write_size,
					int player_id);

/*
** VM QUERY
*/

int				get_player_nbr(t_vm *vm, int player_id);

/*
** VM SET
*/

void			set_player_alive(t_vm *vm, t_proc *process, int player_id);

/*
** OCP TOOLS
*/

int				get_param_type_from_ocp(char ocp, int param_position);
void			set_params(t_param *param, t_op op, char ocp);
int				ocp_match_instruction_params(t_op op, char ocp);

/*
** PROCESS SET
*/

void			process_set_carry(t_proc *process, t_op op, int value);

#endif
