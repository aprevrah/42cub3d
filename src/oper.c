/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:23:53 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/24 23:22:41 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"


void	rotate(u_vec4 v, u_tmatrix *matrix)
{	
	if (v.f.x != 0)
		*matrix = multiply_tmats(rotation_m_x(v.f.x), *matrix);
	if (v.f.y != 0)
		*matrix = multiply_tmats(rotation_m_y(v.f.y), *matrix);
	if (v.f.z != 0)
		*matrix = multiply_tmats(rotation_m_z(v.f.z), *matrix);
}

void	translate(u_vec4 v, u_tmatrix *matrix)
{
	*matrix = multiply_tmats(translate_m(v), *matrix);
}

void	scale(u_vec4 v, u_tmatrix *matrix)
{
	*matrix = multiply_tmats(scale_m(v), *matrix);
}