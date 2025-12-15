/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:00:00 by matis             #+#    #+#             */
/*   Updated: 2025/12/14 17:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->plr->pos_x + data->plr->dir_x * MOVESPEED;
	new_y = data->plr->pos_y + data->plr->dir_y * MOVESPEED;
	return (validate_move(data, new_x, new_y));
}

static int	move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->plr->pos_x - data->plr->dir_x * MOVESPEED;
	new_y = data->plr->pos_y - data->plr->dir_y * MOVESPEED;
	return (validate_move(data, new_x, new_y));
}

static int	move_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->plr->pos_x + data->plr->dir_y * MOVESPEED;
	new_y = data->plr->pos_y - data->plr->dir_x * MOVESPEED;
	return (validate_move(data, new_x, new_y));
}

static int	move_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->plr->pos_x - data->plr->dir_y * MOVESPEED;
	new_y = data->plr->pos_y + data->plr->dir_x * MOVESPEED;
	return (validate_move(data, new_x, new_y));
}

int	move_player(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->plr->move_y == 1)
		moved += move_forward(data);
	if (data->plr->move_y == -1)
		moved += move_backward(data);
	if (data->plr->move_x == -1)
		moved += move_left(data);
	if (data->plr->move_x == 1)
		moved += move_right(data);
	if (data->plr->rotate != 0)
		moved += rotate_player(data, data->plr->rotate);
	return (moved);
}
