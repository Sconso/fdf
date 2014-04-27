/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 19:37:35 by sconso            #+#    #+#             */
/*   Updated: 2014/04/27 19:57:55 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <mlx.h>
#include <ft_fc_conversion.h>

void		debug(t_mdata *md)
{
	mlx_string_put(md->mptr, md->wptr, md->w - 120, 20, 0xFF0000, "Espace: ");
	mlx_string_put(md->mptr, md->wptr, md->w - 120, 30, 0xFF0000, "Angle: ");
	mlx_string_put(md->mptr, md->wptr, md->w - 120, 40, 0xFF0000, "Hauteur: ");
	mlx_string_put(md->mptr, md->wptr, md->w - 120, 50, 0xFF0000, "X: ");
	mlx_string_put(md->mptr, md->wptr, md->w - 120, 60, 0xFF0000, "Y: ");
	mlx_string_put(md->mptr, md->wptr, md->w - 40, 20, 0xFF0000,
					ft_itoa(md->espace));
	mlx_string_put(md->mptr, md->wptr, md->w - 40, 30, 0xFF0000,
					ft_itoa(md->angle));
	mlx_string_put(md->mptr, md->wptr, md->w - 40, 40, 0xFF0000,
					ft_itoa(md->hauteur));
	mlx_string_put(md->mptr, md->wptr, md->w - 40, 50, 0xFF0000,
					ft_itoa(md->x));
	mlx_string_put(md->mptr, md->wptr, md->w - 40, 60, 0xFF0000,
					ft_itoa(md->y));
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
