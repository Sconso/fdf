/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sconso <sconso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 19:40:59 by sconso            #+#    #+#             */
/*   Updated: 2014/04/27 22:20:08 by sconso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdlib.h>

static int		one_shot(int keycode, t_mdata *mdata)
{
	if (keycode == ECHAP)
		exit(0);
	else if (keycode == NUM_0 || keycode == NUMPAD_0)
		reset_values(mdata);
	else if (keycode == SPACE)
		mdata->debug = (mdata->debug ? 0 : 1);
	else if (keycode == NUM_1 || keycode == NUMPAD_1)
		mdata->shadows = (mdata->shadows ? 0 : 1);
	else if (keycode == 47)
	{
		mdata->keys->more_angle = (mdata->keys->more_angle ? 0 : 1);
		mdata->keys->less_angle = 0;
	}
	else if (keycode == 46)
	{
		mdata->keys->less_angle = (mdata->keys->less_angle ? 0 : 1);
		mdata->keys->more_angle = 0;
	}
	else
		return (0);
	expose(mdata);
	return (1);
}

static void		move_keys(int keycode, t_mdata *mdata)
{
	if (keycode == RIGHT)
		mdata->keys->more_angle = 1;
	else if (keycode == LEFT)
		mdata->keys->less_angle = 1;
	if (keycode == UP)
		mdata->keys->more_height = 1;
	else if (keycode == DOWN)
		mdata->keys->less_height = 1;
}

int				key_release(int keycode, t_mdata *mdata)
{
	if (keycode == RIGHT)
		mdata->keys->more_angle = 0;
	else if (keycode == LEFT)
		mdata->keys->less_angle = 0;
	if (keycode == UP)
		mdata->keys->more_height = 0;
	else if (keycode == DOWN)
		mdata->keys->less_height = 0;
	if (keycode == PLUS || keycode == NUMPAD_PLUS)
		mdata->keys->zoom = 0;
	else if (keycode == MINUS || keycode == NUMPAD_MINUS)
		mdata->keys->unzoom = 0;
	if (keycode == W)
		mdata->keys->up = 0;
	else if (keycode == S)
		mdata->keys->down = 0;
	if (keycode == A)
		mdata->keys->left = 0;
	else if (keycode == D)
		mdata->keys->right = 0;
	if (keycode == NUMPAD_8 || keycode == NUMPAD_2)
		mdata->keys->rot_z = 0;
	return (0);
}

int				key_press(int keycode, t_mdata *mdata)
{
	if (one_shot(keycode, mdata))
		return (0);
	move_keys(keycode, mdata);
	if (keycode == PLUS || keycode == NUMPAD_PLUS)
		mdata->keys->zoom = 1;
	else if (keycode == MINUS || keycode == NUMPAD_MINUS)
		mdata->keys->unzoom = 1;
	if (keycode == W)
		mdata->keys->up = 1;
	else if (keycode == S)
		mdata->keys->down = 1;
	if (keycode == A)
		mdata->keys->left = 1;
	else if (keycode == D)
		mdata->keys->right = 1;
	if (keycode == NUMPAD_8)
		mdata->keys->rot_z = 1;
	else if (keycode == NUMPAD_2)
		mdata->keys->rot_z = -1;
	return (0);
}
