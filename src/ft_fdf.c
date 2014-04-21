/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 20:23:33 by sconso            #+#    #+#             */
/*   Updated: 2014/04/22 00:10:46 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <ft_fc_conversion.h>
#include <fcntl.h>

#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#include <stdio.h>

t_vertex		to_vertex(int x, int y, int z, int color)
{
	t_vertex	v;

	v.x = (float)x;
	v.y = (float)y;
	v.z = (float)z;
	v.w = 1.0;
	v.color = color;
	return (v);
}

void			draw_line(t_vertex v1, t_vertex v2, t_mdata *mdata)
{
	t_delta		delta;

	delta.x1 = 1;
	delta.y1 = 2;
	delta.x2 = fabs(v1.x - v2.x);
	delta.y2 = fabs(v1.y - v2.y);
	if (delta.y2 && delta.x2 / delta.y2 < 1)
		delta.x1 = (delta.y2 ? delta.x2 / delta.y2 : 0);
	else if (delta.x2)
		delta.y1 = (delta.x2 ? delta.y2 / delta.x2 : 0);
	while (abs(v1.x - v2.x) >= 1 || abs(v1.y - v2.y) >= 1)
	{
		mlx_pixel_put(mdata->mptr, mdata->wptr, v1.x, v1.y, v1.color);
		if (v1.x < v2.x)
			v1.x += delta.x1;
		else if (v1.x > v2.x)
			v1.x -= delta.x1;
		if (v1.y < v2.y)
			v1.y += delta.y1;
		else if (v1.y > v2.y)
			v1.y -= delta.y1;
	}
}

void		draw_map(t_mdata *mdata)
{
	int		x;
	int		y;
	int		posx1;
	int		posy1;
	int		posx2;
	int		posy2;

	y = -1;
	while (mdata->map[++y] && mdata->map[y + 1])
	{
		x = -1;
		while (mdata->map[y][++x] != -999 && mdata->map[y][x + 1] != -999)
		{
			posx1 = x * ESPACE + (mdata->w / 7) + (y * ANGLE);
			posy1 = (y * ESPACE) + (mdata->h / 6) - (mdata->map[y][x] * HAUTEUR);
			posx2 = (x + 1) * ESPACE + (mdata->w / 7) + (y * ANGLE);
			posy2 = (y * ESPACE) + (mdata->h / 6) - (mdata->map[y][x + 1] * HAUTEUR);

			draw_line(to_vertex(posx1, posy1, 0, 65000),
					  to_vertex(posx2, posy2, 0, 65000),
					  mdata);

			posx1 = x * ESPACE + (mdata->w / 7) + (y * ANGLE);
			posy1 = (y * ESPACE) + (mdata->h / 6) - (mdata->map[y][x] * HAUTEUR);
			posx2 = x * ESPACE + (mdata->w / 7) + ((y + 1) * ANGLE);
			posy2 = ((y + 1) * ESPACE) + (mdata->h / 6) - (mdata->map[y + 1][x] * HAUTEUR);

			draw_line(to_vertex(posx1, posy1, 0, 65000),
					  to_vertex(posx2, posy2, 0, 65000),
					  mdata);

/*			mlx_pixel_put(mdata->mptr, mdata->wptr, x * ESPACE + (mdata->w / 3), y * ESPACE + (mdata->h / 6), 65000);*/
		}
	}
}

int			**ft_init(char *map)
{
	int		fd;
	int		**matrix;

	ft_ext(map, ".fdf");
	fd = ft_open(map, O_RDONLY);
	matrix = create_matrix(fd);
	ft_close(fd);
	fd = ft_open(map, O_RDONLY);
	matrix = fill_matrix(fd, matrix);
	return (matrix);
}

int				key_press(int keycode)
{
	if (keycode == 65307)
		exit(0);
	return (0);
}

int				expose(t_mdata *mdata)
{
	print_matrix(mdata->map);
	draw_map(mdata);
	return (0);
}

t_mdata			*init_mlx(int **map, int userwidth, int userheight)
{
	t_mdata		*mdata;

	mdata = (t_mdata *)malloc(sizeof(t_mdata));
	ft_assert(mdata != NULL, "Cant malloc the mdata... Exiting...\n");
	mdata->w = (userwidth > 0 ? userwidth : 900);
	mdata->h = (userheight > 0 ? userheight : mdata->w * 9 / 16);
	mdata->map = map;
	mdata->mptr = mlx_init();
	mdata->wptr = mlx_new_window(mdata->mptr, mdata->w, mdata->h, "FDF");
	mlx_key_hook(mdata->wptr, key_press, NULL);
	mlx_expose_hook(mdata->wptr, expose, mdata);
	mlx_loop(mdata->mptr);
	return (mdata);
}

int			main(int ac, char **av)
{
	int		**matrix;

	ft_assert(ac >= 2, "Usage: ./fdf map.fdf [width] [height]\n");
	matrix = ft_init(av[1]);
	if (ac == 3)
		init_mlx(matrix, ft_atoi(av[2]), -1);
	else if (ac == 4)
		init_mlx(matrix, ft_atoi(av[2]), ft_atoi(av[3]));
	else
		init_mlx(matrix, -1, -1);
	return (0);
}
