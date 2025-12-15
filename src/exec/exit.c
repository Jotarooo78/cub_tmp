/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:00:00 by matis             #+#    #+#             */
/*   Updated: 2025/12/14 17:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_data *data)
{
	int	i;

	if (data->textures)
	{
		i = 0;
		while (i < 4)
		{
			if (data->textures[i])
				free(data->textures[i]);
			i++;
		}
		free(data->textures);
		data->textures = NULL;
	}
	if (data->tex_pixels)
	{
		free_tab((void **)data->tex_pixels);
		data->tex_pixels = NULL;
	}
}

static void	free_text(t_text *text)
{
	if (!text)
		return ;
	if (text->no)
		free(text->no);
	if (text->so)
		free(text->so);
	if (text->ea)
		free(text->ea);
	if (text->we)
		free(text->we);
	if (text->fl)
		free(text->fl);
	if (text->ce)
		free(text->ce);
	free(text);
}

static void	free_mlx(t_data *data)
{
	if (data->win && data->mlx)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		data->mlx = NULL;
	}
}

void	clean_exit(t_data *data, int code)
{
	if (!data)
		exit(code);
	free_textures(data);
	free_mlx(data);
	if (data->map)
		free_array(data->map);
	if (data->plr)
		free(data->plr);
	free_text(data->text);
	free(data);
	exit(code);
}

int	quit_cub3d(t_data *data)
{
	clean_exit(data, 0);
	return (0);
}
