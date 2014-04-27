/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 20:23:33 by sconso            #+#    #+#             */
/*   Updated: 2014/04/27 16:06:43 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <ft_fc_conversion.h>
#include <stdio.h>





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
