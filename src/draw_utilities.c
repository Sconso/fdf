/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 15:22:26 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/04/27 15:40:51 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int				ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

t_vertex		to_vertex(float x, float y, float z, int color)
{
	t_vertex	v;

	v.x = (float)x;
	v.y = (float)y;
	v.z = (float)z;
	v.w = 1.0;
	v.color = color;
	return (v);
}
