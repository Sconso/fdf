/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 20:39:26 by sconso            #+#    #+#             */
/*   Updated: 2014/04/23 18:04:31 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ESPACE (15)
# define ANGLE (0)
# define HAUTEUR (0)

typedef struct		s_mdata
{
	void			*mptr;
	void			*wptr;
	int				w;
	int				h;
	int				**map;
	int				espace;
	int				angle;
	float			hauteur;
	float			x;
	float			y;
	char			debug;
}					t_mdata;

typedef struct		s_vertex
{
	float			x;
	float			y;
	float			z;
	float			w;
	float			color;
}					t_vertex;

typedef struct		s_delta
{
	float			x1;
	float			x2;
	float			y1;
	float			y2;
}					t_delta;

/*
** ft_errors.c
*/
void	ft_exit(char *str);
void	ft_assert(int check, char *str);
void	ft_strerror(int errnum);
void	ft_error(char *line, int lnb, char *str);

/*
** ft_fdf.c
*/

/*
** ft_file.c
*/
int		ft_open(char *file, int mode);
void	ft_close(int fd);
void	ft_ext(char *file, char *ext);

/*
** ft_matrix.c
*/
int		**create_matrix(int fd);
int		**fill_matrix(int fd, int **matrix);
void	print_matrix(int **matrix);

#endif
