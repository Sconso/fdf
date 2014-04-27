/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/21 20:39:26 by sconso            #+#    #+#             */
/*   Updated: 2014/04/27 21:11:33 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ESPACE (15)
# define ANGLE (0)
# define HAUTEUR (1)
# define ECHAP (65307)
# define SPACE (32)
# define RIGHT (65363)
# define LEFT (65361)
# define UP (65362)
# define DOWN (65364)
# define MINUS (45)
# define PLUS (61)
# define W (119)
# define A (97)
# define S (115)
# define D (100)
# define NUM_0 (48)
# define NUM_1 (49)
# define NUMPAD_PLUS (65451)
# define NUMPAD_MINUS (65453)
# define NUMPAD_0 (65456)
# define NUMPAD_1 (65457)
# define NUMPAD_2 (65458)
# define NUMPAD_3 (65459)
# define NUMPAD_4 (65460)
# define NUMPAD_5 (65461)
# define NUMPAD_6 (65462)
# define NUMPAD_7 (65463)
# define NUMPAD_8 (65464)
# define NUMPAD_9 (65465)

# include <structs.h>

/*
** draw.c
*/
void		draw_line(t_vertex v1, t_vertex v2, t_mdata *mdata);

/*
** draw_map.c
*/
void		draw_map(t_mdata *mdata);

/*
** draw_utilities.c
*/
int			ft_abs(int nb);
t_vertex	to_vertex(float x, float y, float z, int color);

/*
** ft_errors.c
*/
void		ft_exit(char *str);
void		ft_assert(int check, char *str);
void		ft_strerror(int errnum);
void		ft_error(char *line, int lnb, char *str);

/*
** ft_fdf.c
*/
void		draw_map(t_mdata *mdata);
void		debug(t_mdata *mdata);

/*
** ft_file.c
*/
int			ft_open(char *file, int mode);
void		ft_close(int fd);
void		ft_ext(char *file, char *ext);

/*
** ft_matrix.c
*/
int			**create_matrix(int fd);
int			**fill_matrix(int fd, int **matrix);
void		print_matrix(int **matrix);

/*
** hooks.c
*/
int			expose(t_mdata *mdata);
int			loop(t_mdata *mdata);

/*
** init.c
*/
void		reset_values(t_mdata *mdata);
int			**ft_init(char *map);
t_mdata		*init_mlx(int **map, int userwidth, int userheight);

/*
** key_manager.c
*/
int			key_release(int keycode, t_mdata *mdata);
int			key_press(int keycode, t_mdata *mdata);

#endif
