/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 20:23:33 by sconso            #+#    #+#             */
/*   Updated: 2014/04/27 02:35:25 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <ft_fc_conversion.h>
#include <fcntl.h>

#include <stdlib.h>
#include <mlx.h>
#include "/usr/X11/include/X11/X.h"
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

void			fill_image(t_mdata *mdata, float x, float y, unsigned int color)
{
	int				r;
	int				i;
	int				j;

	if (x < 0 || y < 0 || x > mdata->w || y > mdata->h)
		return ;
	color = mlx_get_color_value(mdata->mptr, color);
	r = ((int)x * 4) + ((int)y * mdata->sizeline);
/* 		data[(i + 50) * mdata->sizeline + 2 * 500] = (color & 0xFF); */
	mdata->idata[r] = (color & 0xFF);
	mdata->idata[r + 1] = (color & 0xFF00) >> 8;
	mdata->idata[r + 2] = (color & 0xFF0000) >> 16;
	if (mdata->shadows)
	{
		i = 0;
		while (++i < ESPACE)
		{
			j = 0;
			while (++j < ESPACE)
			{
				r = (((int)x + i) * 4) + (((int)y + j) * mdata->sizeline);
				mdata->idata[r] = (0x000000 & 0xFF);
				mdata->idata[r + 1] = (0x000000 & 0xFF00) >> 8;
				mdata->idata[r + 2] = (0x000000 & 0xFF0000) >> 16;
			}
		}
	}
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
		/*mlx_pixel_put(mdata->mptr, mdata->wptr, v1.x, v1.y, v1.color);*/
		fill_image(mdata, v1.x, v1.y, v1.color);
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
	while (mdata->map[++y])
	{
		x = -1;
		while (mdata->map[y][++x] != -999)
		{
			if (mdata->map[y][x + 1] != -999)
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
			}
			if (mdata->map[y + 1])
			{
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
			}
/* 			mlx_pixel_put(mdata->mptr, mdata->wptr, x * ESPACE + (mdata->w / 3), y * ESPACE + (mdata->h / 6), 65000); */
		}
	}
	/*printf("Posx1 = %f, posy1 = %f\nPosx2 = %f, posy2 = %f\n\n", posx1, posy1, posx2, posy2);*/
	if (mdata->debug)
		debug(mdata);
	mlx_put_image_to_window(mdata->mptr, mdata->wptr, mdata->iptr, 0, 0);
}

int			**ft_init(char *map)
{
	int		fd;
	int		**matrix;

	ft_ext(map, ".fdf");
	fd = ft_open(map, O_RDWR);
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

void			swap(unsigned int *a, unsigned int *b)
{
	unsigned int c;

	c = *a;
	*a = *b;
	*b = c;
}


int				expose(t_mdata *mdata)
{
/*	print_matrix(mdata->map);*/
	if (mdata->iptr)
		mlx_destroy_image(mdata->mptr, mdata->iptr);
	mdata->iptr = mlx_new_image(mdata->mptr, mdata->w, mdata->h);
	mdata->idata = mlx_get_data_addr(mdata->iptr, &mdata->bpp, &mdata->sizeline, &mdata->endian);
	draw_map(mdata);
	return (0);
}

int				loop(t_mdata *mdata)
{
	char		check;

	check = 0;
	if (mdata->keys->more_angle && (check = 1))
	{
		mdata->angle += .1;
		mdata->x -= 1;
	}
	else if (mdata->keys->less_angle && (check = 1))
	{
		mdata->angle -= .1;
		mdata->x += 1;
	}
	if (mdata->keys->more_height && (check = 1))
		mdata->hauteur += .01;
	else if (mdata->keys->less_height && (check = 1))
		mdata->hauteur -= .01;
	if (mdata->keys->zoom && (check = 1))
		mdata->espace += .1;
	else if (mdata->keys->unzoom && (check = 1))
		mdata->espace -= .1;
	if (mdata->keys->up && (check = 1))
		mdata->y -= 1;
	else if (mdata->keys->down && (check = 1))
		mdata->y += 1;
	if (mdata->keys->left && (check = 1))
		mdata->x -= 1;
	else if (mdata->keys->right && (check = 1))
		mdata->x += 1;
	if (check)
		expose(mdata);
	return (0);
}

int				key_release(int keycode, t_mdata *mdata)
{
	if (keycode == 65363)
		mdata->keys->more_angle = 0;
	else if (keycode == 65361)
		mdata->keys->less_angle = 0;
	if (keycode == 65362)
		mdata->keys->more_height = 0;
	else if (keycode == 65364)
		mdata->keys->less_height = 0;
	if (keycode == 65451 || keycode == 61)
		mdata->keys->zoom = 0;
	else if (keycode == 65453 || keycode == 45)
		mdata->keys->unzoom = 0;
	if (keycode == 119)
		mdata->keys->up = 0;
	else if (keycode == 115)
		mdata->keys->down = 0;
	if (keycode == 97)
		mdata->keys->left = 0;
	else if (keycode == 100)
		mdata->keys->right = 0;
	printf("%d\n", keycode);
	return (0);
}

int				key_press(int keycode, t_mdata *mdata)
{
	if (keycode == 65307)
		exit(0);
	else if (keycode == 65456 || keycode == 48)
	{
		reset_values(mdata);
		expose(mdata);
	}
	else if (keycode == 32)
	{
		mdata->debug = (mdata->debug ? 0 : 1);
		expose(mdata);
	}
	else if (keycode == 49)
	{
		mdata->shadows = (mdata->shadows ? 0 : 1);
		expose(mdata);
	}
	if (keycode == 65363)
		mdata->keys->more_angle = 1;
	else if (keycode == 65361)
		mdata->keys->less_angle = 1;
	if (keycode == 65362)
		mdata->keys->more_height = 1;
	else if (keycode == 65364)
		mdata->keys->less_height = 1;
	if (keycode == 65451 || keycode == 61)
		mdata->keys->zoom = 1;
	else if (keycode == 65453 || keycode == 45)
		mdata->keys->unzoom = 1;
	if (keycode == 119)
		mdata->keys->up = 1;
	else if (keycode == 115)
		mdata->keys->down = 1;
	if (keycode == 97)
		mdata->keys->left = 1;
	else if (keycode == 100)
		mdata->keys->right = 1;
	return (0);
}

t_keys			*init_keys(void)
{
	t_keys		*keys;

	keys = (t_keys *)malloc(sizeof(t_keys));
	ft_assert(keys != NULL, "Cant malloc the keys.. Exiting...\n");
	keys->right = 0;
	keys->left = 0;
	keys->up = 0;
	keys->down = 0;
	keys->more_height = 0;
	keys->less_height = 0;
	keys->more_angle = 0;
	keys->less_angle = 0;
	keys->zoom = 0;
	keys->unzoom = 0;
	return (keys);
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
	mdata->iptr = NULL;
	mdata->keys = init_keys();
	mdata->espace = ESPACE;
	mdata->angle = ANGLE;
	mdata->hauteur = HAUTEUR;
	mdata->debug = 0;
	mdata->shadows = 0;
	mdata->x = 0;
	mdata->y = 0;
	mlx_do_key_autorepeatoff(mdata->mptr);
	mlx_hook(mdata->wptr, KeyPress, KeyPressMask, &key_press, mdata);
	mlx_hook(mdata->wptr, KeyRelease, KeyReleaseMask, &key_release, mdata);
	mlx_expose_hook(mdata->wptr, expose, mdata);
	mlx_loop_hook(mdata->mptr, loop, mdata);
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
