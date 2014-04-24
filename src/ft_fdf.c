/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 20:23:33 by sconso            #+#    #+#             */
/*   Updated: 2014/04/24 00:15:36 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <ft_fc_conversion.h>
#include <fcntl.h>

#include <stdlib.h>
#include <mlx.h>
#include <math.h>


#include <unistd.h>
#include <stdio.h>

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

void			draw_line(t_vertex v1, t_vertex v2, t_mdata *mdata)
{
	t_delta		delta;

	delta.x1 = 1;
	delta.y1 = 1;
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

void		debug(t_mdata *mdata)
{
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 100, 20, 175000, "Espace: ");
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 100, 30, 175000, "Angle: ");
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 100, 40, 175000, "Hauteur: ");
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 100, 50, 175000, "X: ");
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 100, 60, 175000, "Y: ");
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 20, 20, 175000, ft_itoa(mdata->espace));
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 20, 30, 175000, ft_itoa(mdata->angle));
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 20, 40, 175000, ft_itoa(mdata->hauteur));
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 20, 50, 175000, ft_itoa(mdata->x));
	mlx_string_put(mdata->mptr, mdata->wptr, mdata->w - 20, 60, 175000, ft_itoa(mdata->y));
}

void		draw_map(t_mdata *mdata)
{
	int		x;
	int		y;
	float	posx1;
	float	posy1;
	float	posx2;
	float	posy2;
	int		color1;
	int		color2;

	y = -1;
	while (mdata->map[++y] && mdata->map[y + 1])
	{
		x = -1;
		while (mdata->map[y][++x] != -999 && mdata->map[y][x + 1] != -999)
		{
			posx1 = (x * mdata->espace) + mdata->x;
			posy1 = (y * mdata->espace) + mdata->y;
			posx2 = ((x + 1) * mdata->espace) + mdata->x;
			posy2 = (y * mdata->espace) + mdata->y;
 			posx1 += y * mdata->angle;
 			posy1 -= mdata->map[y][x] * mdata->hauteur;
 			posx2 += y * mdata->angle;
 			posy2 -= mdata->map[y][x + 1] * mdata->hauteur;

			color1 = (0 << 16) + (200 << 8) + 0;
			color1 += ((int)(mdata->map[y][x] * mdata->hauteur * 3) << 16) % 255;
			color1 += ((int)(mdata->map[y][x] * mdata->hauteur * 3) << 8) % 255;
			color1 += (int)(mdata->map[y][x] * mdata->hauteur * 3) % 255;
			color2 = color1;
			draw_line(to_vertex(posx1, posy1, 0, color1),
					  to_vertex(posx2, posy2, 0, color2),
					  mdata);

			posx1 = (x * mdata->espace) + mdata->x;
			posy1 = (y * mdata->espace) + mdata->y;
			posx2 = (x * mdata->espace) + mdata->x;
			posy2 = ((y + 1) * mdata->espace) + mdata->y;

			posx1 += y * mdata->angle;
			posy1 -= mdata->map[y][x] * mdata->hauteur;
			posx2 += (y + 1) * mdata->angle;
			posy2 -= mdata->map[y + 1][x] * mdata->hauteur;

			draw_line(to_vertex(posx1, posy1, 0, color1),
					  to_vertex(posx2, posy2, 0, color2),
					  mdata);
/* 			mlx_pixel_put(mdata->mptr, mdata->wptr, x * ESPACE + (mdata->w / 3), y * ESPACE + (mdata->h / 6), 65000); */
		}
	}
	printf("Posx1 = %f, posy1 = %f\nPosx2 = %f, posy2 = %f\n\n", posx1, posy1, posx2, posy2);
	if (mdata->debug)
		debug(mdata);
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

void			reset_values(t_mdata *mdata)
{
	mdata->espace = ESPACE;
	mdata->angle = ANGLE;
	mdata->hauteur = HAUTEUR;
}

int				expose(t_mdata *mdata)
{
	print_matrix(mdata->map);
	draw_map(mdata);
	return (0);
}

int				key_press(int keycode, t_mdata *mdata)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 65363)
		mdata->angle++;
	else if (keycode == 65361)
		mdata->angle--;
	else if (keycode == 65362)
		mdata->hauteur += 0.2;
	else if (keycode == 65364)
		mdata->hauteur -= 0.2;
	else if (keycode == 65451)
		mdata->espace++;
	else if (keycode == 65453)
		mdata->espace--;
	else if (keycode == 65456)
		reset_values(mdata);
	else if (keycode == 32)
		mdata->debug = (mdata->debug ? 0 : 1);
	else if (keycode == 119)
		mdata->y -= 5;
	else if (keycode == 97)
		mdata->x -= 5;
	else if (keycode == 115)
		mdata->y += 5;
	else if (keycode == 100)
		mdata->x += 5;
	else
		printf("%d\n", keycode);
	mlx_clear_window(mdata->mptr, mdata->wptr);
	expose(mdata);
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
	mdata->iptr = mlx_new_image(mdata->mptr, mdata->w, mdata->h);
	mdata->espace = ESPACE;
	mdata->angle = ANGLE;
	mdata->hauteur = HAUTEUR;
	mdata->debug = 0;
	mdata->x = 0;
	mdata->y = 0;
	mlx_key_hook(mdata->wptr, key_press, mdata);
	mlx_expose_hook(mdata->wptr, expose, mdata);
/*	mlx_loop_hook(mdata->mptr, loop_hook, mdata);*/
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
