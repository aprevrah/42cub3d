/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:23:53 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/24 18:11:44 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

u_tmatrix	*get_matrix(char mchar, t_data *data)
{
	if (mchar == 'o')
		return (&(data->obj_tmat));
	return (&(data->view_tmat));
}

void	rot_x(int value, char matrix_char, void *data)
{
	u_tmatrix	*matrix;
	
	matrix = get_matrix(matrix, data);
	multiply_tmats(rotation_m_x(value * OPER_FACTOR), *matrix);
}

void	rot_y(int value, char matrix_char, void *data)
{
	u_tmatrix	*matrix;
	
	matrix = get_matrix(matrix, data);
	multiply_tmats(rotation_m_y(value * OPER_FACTOR), *matrix);
}

void	rot_z(int value, char matrix_char, void *data)
{
	u_tmatrix	*matrix;
	
	matrix = get_matrix(matrix, data);
	multiply_tmats(rotation_m_z(value * OPER_FACTOR), *matrix);
}