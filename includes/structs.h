/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 19:42:17 by sconso            #+#    #+#             */
/*   Updated: 2014/04/27 21:43:32 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct		s_keys
{
	char			right;
	char			left;
	char			up;
	char			down;
	char			more_height;
	char			less_height;
	char			more_angle;
	char			less_angle;
	char			zoom;
	char			unzoom;
	char			rot_z;
}					t_keys;

typedef struct		s_mdata
{
	void			*mptr;
	void			*wptr;
	void			*iptr;
	char			*idata;
	t_keys			*keys;
	int				w;
	int				h;
	int				**map;
	float			espace_x;
	float			espace_y;
	float			angle;
	float			hauteur;
	float			x;
	float			y;
	int				sx;
	int				sy;
	int				bpp;
	int				sizeline;
	int				endian;
	char			debug;
	char			shadows;
}					t_mdata;

typedef struct		s_vertex
{
	float			x;
	float			y;
	float			z;
	float			w;
	unsigned int	color;
}					t_vertex;

typedef struct		s_delta
{
	float			x1;
	float			x2;
	float			y1;
	float			y2;
}					t_delta;

#endif
