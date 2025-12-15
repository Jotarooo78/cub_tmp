/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:00:00 by matis             #+#    #+#             */
/*   Updated: 2025/12/14 17:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_dir_north_south(t_player *plr, char dir)
{
	if (dir == 'S')
	{
		plr->dir_x = 0;
		plr->dir_y = 1;
		plr->plane_x = -0.66;
		plr->plane_y = 0;
	}
	else if (dir == 'N')
	{
		plr->dir_x = 0;
		plr->dir_y = -1;
		plr->plane_x = 0.66;
		plr->plane_y = 0;
	}
}

static void	init_dir_east_west(t_player *plr, char dir)
{
	if (dir == 'W')
	{
		plr->dir_x = -1;
		plr->dir_y = 0;
		plr->plane_x = 0;
		plr->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		plr->dir_x = 1;
		plr->dir_y = 0;
		plr->plane_x = 0;
		plr->plane_y = 0.66;
	}
}

void	init_player(t_data *data)
{
	data->plr->pos_x = (double)data->p_x + 0.5;
	data->plr->pos_y = (double)data->p_y + 0.5;
	data->plr->dir_x = 0;
	data->plr->dir_y = 0;
	data->plr->plane_x = 0;
	data->plr->plane_y = 0;
	data->plr->has_moved = 0;
	data->plr->move_x = 0;
	data->plr->move_y = 0;
	data->plr->rotate = 0;
	init_dir_north_south(data->plr, data->player);
	init_dir_east_west(data->plr, data->player);
}
