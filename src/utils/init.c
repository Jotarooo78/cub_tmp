/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:37:25 by messengu          #+#    #+#             */
/*   Updated: 2025/12/14 17:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_putstr_fd("Error\nFailed to init mlx\n", 2), 1);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!data->win)
		return (ft_putstr_fd("Error\nFailed to init window\n", 2), 1);
	return (0);
}

static int	init_player_struct(t_data *data)
{
	data->plr = malloc(sizeof(t_player));
	if (!data->plr)
		return (ft_putstr_fd("Error\nFailed to alloc player\n", 2), 1);
	ft_bzero(data->plr, sizeof(t_player));
	return (0);
}

static void	init_data_values(t_data *data)
{
	data->textures = NULL;
	data->tex_pixels = NULL;
	data->hex_floor = 0;
	data->hex_ceiling = 0;
	data->texinfo.size = TEX_SIZE;
	data->texinfo.index = 0;
	data->texinfo.x = 0;
	data->texinfo.y = 0;
	data->texinfo.step = 0;
	data->texinfo.pos = 0;
}

static void	render_first_frame(t_data *data)
{
	data->plr->has_moved = 1;
	render(data);
}

int	init_game_data(t_data *data)
{
	init_data_values(data);
	if (init_window(data))
		return (1);
	if (init_player_struct(data))
		return (clean_exit(data, 1), 1);
	init_player(data);
	init_textures(data);
	render_first_frame(data);
	listen_for_input(data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	return (0);
}
