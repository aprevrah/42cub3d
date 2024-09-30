/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:32 by aprevrha          #+#    #+#             */
/*   Updated: 2024/09/30 15:29:07 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// New Vector = nv
t_vec4	nv(float x, float y, float z)
{
	t_vec4	v;

	v.f.x = x;
	v.f.y = y;
	v.f.z = z;
	v.f.w = 1;
	return (v);
}

t_vec4	left_multiply(t_tmatrix mat, t_vec4 vec)
{
	t_vec4	result;

	result.f.x = vec.f.x * mat.f.x1 + vec.f.y * mat.f.y1 + vec.f.z * mat.f.z1
		+ vec.f.w * mat.f.w1;
	result.f.y = vec.f.x * mat.f.x2 + vec.f.y * mat.f.y2 + vec.f.z * mat.f.z2
		+ vec.f.w * mat.f.w2;
	result.f.z = vec.f.x * mat.f.x3 + vec.f.y * mat.f.y3 + vec.f.z * mat.f.z3
		+ vec.f.w * mat.f.w3;
	result.f.w = vec.f.x * mat.f.x4 + vec.f.y * mat.f.y4 + vec.f.z * mat.f.z4
		+ vec.f.w * mat.f.w4;
	return (result);
}

t_tmatrix	multiply_tmats(t_tmatrix mat1, t_tmatrix mat2)
{
	t_tmatrix	result;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			result.arr[i * 4 + j] = 0;
			k = 0;
			while (k < 4)
			{
				result.arr[i * 4 + j] += mat1.arr[i * 4 + k] * mat2.arr[k * 4
					+ j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (result);
}
