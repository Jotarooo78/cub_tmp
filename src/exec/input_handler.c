/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:00:00 by matis             #+#    #+#             */
/*   Updated: 2025/12/15 11:03:12 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_Left)
		data->plr->rotate = -1;
	if (key == XK_Right)
		data->plr->rotate = 1;
	if (key == XK_w)
		data->plr->move_y = 1;
	if (key == XK_a)
		data->plr->move_x = -1;
	if (key == XK_s)
		data->plr->move_y = -1;
	if (key == XK_d)
		data->plr->move_x = 1;
	return (0);
}

static int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_w && data->plr->move_y == 1)
		data->plr->move_y = 0;
	if (key == XK_s && data->plr->move_y == -1)
		data->plr->move_y = 0;
	if (key == XK_a && data->plr->move_x == -1)
		data->plr->move_x = 0;
	if (key == XK_d && data->plr->move_x == 1)
		data->plr->move_x = 0;
	if (key == XK_Left && data->plr->rotate == -1)
		data->plr->rotate = 0;
	if (key == XK_Right && data->plr->rotate == 1)
		data->plr->rotate = 0;
	return (0);
}

void	listen_for_input(t_data *data)
{
	mlx_hook(data->win, DESTROY_NOTIFY, NO_EVENT_MASK, quit_cub3d, data);
	mlx_hook(data->win, KEY_PRESS, KEY_PRESS_MASK, key_press_handler, data);
	mlx_hook(data->win, KEY_RELEASE, KEY_RELEASE_MASK,
		key_release_handler, data);
}
