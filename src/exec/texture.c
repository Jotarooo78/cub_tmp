/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:00:00 by matis             #+#    #+#             */
/*   Updated: 2025/12/14 17:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_tex_pixels(t_data *data)
{
	int	i;

	if (data->tex_pixels)
		free_tab((void **)data->tex_pixels);
	data->tex_pixels = ft_calloc(WIN_HEIGHT + 1, sizeof(int *));
	if (!data->tex_pixels)
		clean_exit(data, 1);
	i = 0;
	while (i < WIN_HEIGHT)
	{
		data->tex_pixels[i] = ft_calloc(WIN_WIDTH + 1, sizeof(int));
		if (!data->tex_pixels[i])
			clean_exit(data, 1);
		i++;
	}
}

static void	get_tex_index(t_data *data, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->texinfo.index = WEST;
		else
			data->texinfo.index = EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			data->texinfo.index = SOUTH;
		else
			data->texinfo.index = NORTH;
	}
}

static void	calc_tex_pos(t_data *data, t_ray *ray)
{
	t_texinfo	*tex;

	tex = &data->texinfo;
	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - WIN_HEIGHT / 2
			+ ray->line_height / 2) * tex->step;
}

void	update_tex_pixels(t_data *data, t_ray *ray, int x)
{
	t_texinfo	*tex;
	int			y;
	int			color;

	get_tex_index(data, ray);
	calc_tex_pos(data, ray);
	tex = &data->texinfo;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->textures[tex->index][tex->size * tex->y + tex->x];
		if (tex->index == NORTH || tex->index == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->tex_pixels[y][x] = color;
		y++;
	}
}
