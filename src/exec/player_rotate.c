/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:00:00 by matis             #+#    #+#             */
/*   Updated: 2025/12/14 17:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rotate_left_right(t_player *plr, double rotspeed)
{
	double	tmp_x;

	tmp_x = plr->dir_x;
	plr->dir_x = plr->dir_x * cos(rotspeed) - plr->dir_y * sin(rotspeed);
	plr->dir_y = tmp_x * sin(rotspeed) + plr->dir_y * cos(rotspeed);
	tmp_x = plr->plane_x;
	plr->plane_x = plr->plane_x * cos(rotspeed) - plr->plane_y * sin(rotspeed);
	plr->plane_y = tmp_x * sin(rotspeed) + plr->plane_y * cos(rotspeed);
	return (1);
}

int	rotate_player(t_data *data, double rotdir)
{
	int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROTSPEED * rotdir;
	moved += rotate_left_right(data->plr, rotspeed);
	return (moved);
}

static bool	is_valid_pos(t_data *data, double x, double y)
{
	if (x < 0.25 || x >= data->map_x - 0.25)
		return (false);
	if (y < 0.25 || y >= data->map_y - 0.25)
		return (false);
	if (data->map[(int)y][(int)x] == '1')
		return (false);
	return (true);
}

int	validate_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(data, new_x, data->plr->pos_y))
	{
		data->plr->pos_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(data, data->plr->pos_x, new_y))
	{
		data->plr->pos_y = new_y;
		moved = 1;
	}
	return (moved);
}
