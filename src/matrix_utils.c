/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprevrha <aprevrha@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:24:32 by aprevrha          #+#    #+#             */
/*   Updated: 2024/02/25 03:02:47 by aprevrha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

//New Vector = nv
u_vec4 nv(float x, float y, float z)
{
	u_vec4 v;
	
	v.f.x = x;
	v.f.y = y;
	v.f.z = z;
	v.f.w = 1;
	return (v);
}

// Function to create a rotation matrix for rotation about the x-axis by an angle in radians
u_tmatrix rotation_m_x(float angle)
{
    float cos_theta = cos(angle);
    float sin_theta = sin(angle);

    u_tmatrix result = {0};
    result.f.x1 = 1;
    result.f.y2 = cos_theta;
    result.f.z2 = -sin_theta;
    result.f.y3 = sin_theta;
    result.f.z3 = cos_theta;
    result.f.w4 = 1;

    return (result);
}

// Function to create a rotation matrix for rotation about the y-axis by an angle in radians
u_tmatrix rotation_m_y(float angle)
{
    float cos_theta = cos(angle);
    float sin_theta = sin(angle);

    u_tmatrix result = {0};
    result.f.x1 = cos_theta;
    result.f.z1 = sin_theta;
    result.f.y2 = 1;
    result.f.x3 = -sin_theta;
    result.f.z3 = cos_theta;
    result.f.w4 = 1;

    return (result);
}

// Function to create a rotation matrix for rotation about the z-axis by an angle in radians
u_tmatrix rotation_m_z(float angle)
{
    float cos_theta = cos(angle);
    float sin_theta = sin(angle);

    u_tmatrix result = {0};
    result.f.x1 = cos_theta;
    result.f.y1 = -sin_theta;
    result.f.x2 = sin_theta;
    result.f.y2 = cos_theta;
    result.f.z3 = 1;
    result.f.w4 = 1;

    return (result);
}

u_tmatrix scale_m(u_vec4 vec)
{
    u_tmatrix result = {0};
    result.f.x1 = vec.f.x;
    result.f.y2 = vec.f.y;
    result.f.z3 = vec.f.z;
    result.f.w4 = 1;

    return (result);
}

u_tmatrix translate_m(u_vec4 vec)
{
    u_tmatrix result = {0};
    result.f.x1 = 1;
    result.f.y2 = 1;
    result.f.z3 = 1;
    result.f.w4 = 1;

    result.f.w1 = vec.f.x;
    result.f.w2 = vec.f.y;
    result.f.w3 = vec.f.z;

    return (result);
}

u_tmatrix	perspec_project_m(float n, float f)
{
    u_tmatrix result = {0};
    result.f.x1 = 1;
    result.f.y2 = 1;
    result.f.z3 = (f/(f-n));
	result.f.z4 = ((f*n)/(f-n));
    result.f.w3 = 1;
	result.f.w4 = 0;

    return (result);
}

u_vec4	perspec_div(u_vec4 vec)
{
	// int i;
	
	// printf("perspec_div");
	// i = 0;
	// while (i < 4)
	// {
	// 	vec.arr[i] /= vec.f.w;
	// 	i++;
	// }
	float inv_w = 1.0/vec.f.w;
	vec.f.x *= inv_w;
	vec.f.y *= inv_w;
	vec.f.z *= inv_w;
	vec.f.w = 1;
	return (vec);
}

u_tmatrix multiply_tmats(u_tmatrix mat1, u_tmatrix mat2)
{
    u_tmatrix result;
	int i;
	int j;
	int k;

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
                result.arr[i * 4 + j] += mat1.arr[i * 4 + k] * mat2.arr[k * 4 + j];
                k++;
            }
            j++;
        }
        i++;
    }
    return (result);
}