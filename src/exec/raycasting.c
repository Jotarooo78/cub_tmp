/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:00:00 by matis             #+#    #+#             */
/*   Updated: 2025/12/14 17:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray_dir(int x, t_ray *ray, t_player *plr)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir_x = plr->dir_x + plr->plane_x * ray->camera_x;
	ray->dir_y = plr->dir_y + plr->plane_y * ray->camera_x;
	ray->map_x = (int)plr->pos_x;
	ray->map_y = (int)plr->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static void	set_dda(t_ray *ray, t_player *plr)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (plr->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - plr->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (plr->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - plr->pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_x < 0
			|| ray->map_y >= data->map_y || ray->map_x >= data->map_x)
			break ;
		if (data->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static void	calc_line_height(t_ray *ray, t_player *plr)
{
	if (ray->side == 0)
		ray->wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = plr->pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = plr->pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

int	raycasting(t_data *data)
{
	t_ray	*ray;
	int		x;

	x = 0;
	ray = &data->ray;
	while (x < WIN_WIDTH)
	{
		init_ray(ray);
		init_ray_dir(x, ray, data->plr);
		set_dda(ray, data->plr);
		perform_dda(data, ray);
		calc_line_height(ray, data->plr);
		update_tex_pixels(data, ray, x);
		x++;
	}
	return (0);
}
