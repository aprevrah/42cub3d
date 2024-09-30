/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_affine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:32 by aprevrha          #+#    #+#             */
/*   Updated: 2024/09/30 15:29:07 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_tmatrix	rotation_m_x(float angle)
{
	float		cos_theta;
	float		sin_theta;
	t_tmatrix	result;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	ft_bzero(&result, sizeof(result));
	result.f.x1 = 1;
	result.f.y2 = cos_theta;
	result.f.z2 = -sin_theta;
	result.f.y3 = sin_theta;
	result.f.z3 = cos_theta;
	result.f.w4 = 1;
	return (result);
}

t_tmatrix	rotation_m_y(float angle)
{
	float		cos_theta;
	float		sin_theta;
	t_tmatrix	result;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	ft_bzero(&result, sizeof(result));
	result.f.x1 = cos_theta;
	result.f.z1 = sin_theta;
	result.f.y2 = 1;
	result.f.x3 = -sin_theta;
	result.f.z3 = cos_theta;
	result.f.w4 = 1;
	return (result);
}

t_tmatrix	rotation_m_z(float angle)
{
	float		cos_theta;
	float		sin_theta;
	t_tmatrix	result;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	ft_bzero(&result, sizeof(result));
	result.f.x1 = cos_theta;
	result.f.y1 = -sin_theta;
	result.f.x2 = sin_theta;
	result.f.y2 = cos_theta;
	result.f.z3 = 1;
	result.f.w4 = 1;
	return (result);
}

t_tmatrix	scale_m(t_vec4 vec)
{
	t_tmatrix	result;

	ft_bzero(&result, sizeof(result));
	result.f.x1 = vec.f.x;
	result.f.y2 = vec.f.y;
	result.f.z3 = vec.f.z;
	result.f.w4 = 1;
	return (result);
}

t_tmatrix	translate_m(t_vec4 vec)
{
	t_tmatrix	result;

	ft_bzero(&result, sizeof(result));
	result.f.x1 = 1;
	result.f.y2 = 1;
	result.f.z3 = 1;
	result.f.w4 = 1;
	result.f.w1 = vec.f.x;
	result.f.w2 = vec.f.y;
	result.f.w3 = vec.f.z;
	return (result);
}
