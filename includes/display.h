/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 15:44:59 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/07 10:00:05 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "options.h"

# define MEM_H (MEM_SIZE / 64)
# define MEM_W ((MEM_SIZE / 64) * 3)
# define INF_H (MEM_SIZE / 64)
# define INF_W 60
# define NC_KEYS " qnjk"
# define NC_MAX_SPEED 200000
# define NC_SPEED_DELTA 25000
# define VM_INFO_SIZE 3
# define PLAYER_INFO_SIZE 5

void	display_memory(t_vm *vm);
void	init_memory_win(t_win *memory);
int		display_init(t_vm *vm);
void	display_load_player(t_vm *vm, t_player player, int player_id,
	unsigned int start);
void	display_write_memory(t_vm *vm, int start, int size, int player_id);
void	display_update(t_vm *vm);
void	close_ncurse_display(t_vm *vm);
void	display_info(t_vm *vm);
void	display_update_color(t_vm *vm, unsigned int start, int size,
	int player_id);
void	display_update_pc(t_vm *vm, unsigned int pc, int player_id);
void	add_new_pc(t_vm *vm, unsigned int new_pc, int player_id);
void	display_reset_pc_colors(t_vm *vm);

#endif
