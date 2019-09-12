/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 17:33:31 by bopopovi          #+#    #+#             */
/*   Updated: 2019/09/07 00:51:24 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

int		get_param_type_from_ocp(char ocp, int param_position)
{
	return (ocp >> (8 - param_position * 2) & 0x03);
}

int		valid_type_for_op(int type, t_op op, int param_nbr)
{
	if (type == DIR_CODE)
		return ((T_DIR & op.arg_types[param_nbr]) == T_DIR);
	else if (type == IND_CODE)
		return ((T_IND & op.arg_types[param_nbr]) == T_IND);
	else if (type == REG_CODE)
		return ((T_REG & op.arg_types[param_nbr]) == T_REG);
	return (0);
}

int		set_params_from_ocp(t_param *params, t_op op, char ocp)
{
	int i;
	int type;
	int errors;

	i = 0;
	type = 0;
	errors = 0;
	while (i < 4)
	{
		type = get_param_type_from_ocp(ocp, (i + 1));
		errors += (i < op.arg_nbr && !valid_type_for_op(type, op, i));
		params[i].type = type;
		i++;
	}
	return (errors);
}

void	set_params_from_op_info(t_param *params, t_op op)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (i == op.arg_nbr)
			return ;
		if (op.arg_types[i] == T_REG)
			params[i].type = REG_CODE;
		else if (op.arg_types[i] == T_IND)
			params[i].type = IND_CODE;
		else if (op.arg_types[i] == T_DIR)
			params[i].type = DIR_CODE;
		i++;
	}
}
