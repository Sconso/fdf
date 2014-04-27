/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Myrkskog <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/27 14:05:42 by Myrkskog          #+#    #+#             */
/*   Updated: 2014/04/27 15:45:31 by Myrkskog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <stdlib.h>


#include <stdio.h>

static int		one_shot(int keycode, t_mdata *mdata)
{
	if (keycode == ECHAP)
		exit(0);
	else if (keycode == NUM_0)
	{
		reset_values(mdata);
		expose(mdata);
	}
	else if (keycode == SPACE)
	{
		mdata->debug = (mdata->debug ? 0 : 1);
		expose(mdata);
	}
	else if (keycode == NUM_1)
	{
		mdata->shadows = (mdata->shadows ? 0 : 1);
		expose(mdata);
	}
	else
		return (0);
	return (1);
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
	if (keycode == PLUS)
		mdata->keys->zoom = 0;
	else if (keycode == MINUS)
		mdata->keys->unzoom = 0;
	if (keycode == W)
		mdata->keys->up = 0;
	else if (keycode == S)
		mdata->keys->down = 0;
	if (keycode == A)
		mdata->keys->left = 0;
	else if (keycode == D)
		mdata->keys->right = 0;
	printf("%d\n", keycode);
	return (0);
}

int				key_press(int keycode, t_mdata *mdata)
{
	if (one_shot(keycode, mdata))
		return (0);
	if (keycode == RIGHT)
		mdata->keys->more_angle = 1;
	else if (keycode == LEFT)
		mdata->keys->less_angle = 1;
	if (keycode == UP)
		mdata->keys->more_height = 1;
	else if (keycode == DOWN)
		mdata->keys->less_height = 1;
	if (keycode == PLUS)
		mdata->keys->zoom = 1;
	else if (keycode == MINUS)
		mdata->keys->unzoom = 1;
	if (keycode == W)
		mdata->keys->up = 1;
	else if (keycode == S)
		mdata->keys->down = 1;
	if (keycode == A)
		mdata->keys->left = 1;
	else if (keycode == D)
		mdata->keys->right = 1;
	return (0);
}
