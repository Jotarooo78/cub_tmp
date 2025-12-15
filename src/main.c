/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 15:28:12 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/14 17:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_to_0(t_data *data)
{
	data->text->fl->r = 0;
	data->text->fl->g = 0;
	data->text->fl->b = 0;
	data->text->ce->r = 0;
	data->text->ce->g = 0;
	data->text->ce->b = 0;
	data->p_x = 0;
	data->p_y = 0;
	data->map_y = 0;
	data->map_x = 0;
	data->text->no = NULL;
	data->text->so = NULL;
	data->text->we = NULL;
	data->text->ea = NULL;
	data->player = 'X';
	data->plr = NULL;
	data->mlx = NULL;
	data->win = NULL;
}

static t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->map = NULL;
	data->text = malloc(sizeof(t_text));
	if (!data->text)
		return (free(data), NULL);
	data->text->fl = malloc(sizeof(t_color));
	if (!data->text->fl)
		return (free(data->text), free(data), NULL);
	data->text->ce = malloc(sizeof(t_color));
	if (!data->text->ce)
		return (free(data->text->fl), free(data->text), free(data), NULL);
	init_to_0(data);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2 || !argv[1])
	{
		ft_putstr_fd("Error\nUsage: ./cub3D <map.cub>\n", 2);
		return (1);
	}
	if (check_ext(argv[1], ".cub"))
	{
		ft_putstr_fd("Error\nFile must have .cub extension\n", 2);
		return (1);
	}
	data = init_data();
	if (!data)
		return (1);
	if (parse(data, argv[1]) != 0)
		return (1);
	if (init_game_data(data))
		return (1);
	clean_exit(data, 0);
	return (0);
}
