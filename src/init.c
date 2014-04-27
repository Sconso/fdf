/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 14:39:06 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/04/27 14:44:47 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include "/usr/X11/include/X11/X.h"
#include <stdlib.h>
#include <fcntl.h>

static t_keys	*init_keys(void)
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

void			reset_values(t_mdata *mdata)
{
	mdata->espace = ESPACE;
	mdata->angle = ANGLE;
	mdata->hauteur = HAUTEUR;
}

int				**ft_init(char *map)
{
	int			fd;
	int			**matrix;

	ft_ext(map, ".fdf");
	fd = ft_open(map, O_RDWR);
	matrix = create_matrix(fd);
	ft_close(fd);
	fd = ft_open(map, O_RDONLY);
	matrix = fill_matrix(fd, matrix);
	return (matrix);
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
