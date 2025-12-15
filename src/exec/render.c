/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:00:00 by matis             #+#    #+#             */
/*   Updated: 2025/12/15 11:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_frame_pixel(t_data *data, t_img *img, int x, int y)
{
	if (data->tex_pixels[y][x] > 0)
		set_image_pixel(img, x, y, data->tex_pixels[y][x]);
	else if (y < WIN_HEIGHT / 2)
		set_image_pixel(img, x, y, data->hex_ceiling);
	else
		set_image_pixel(img, x, y, data->hex_floor);
}

static void	init_img(t_data *data, t_img *img)
{
	img->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img)
		clean_exit(data, 1);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	render_frame(t_data *data)
{
	t_img	img;
	int		x;
	int		y;

	img.img = NULL;
	init_img(data, &img);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			set_frame_pixel(data, &img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
}

static void	render_raycast(t_data *data)
{
	init_tex_pixels(data);
	init_ray(&data->ray);
	raycasting(data);
	render_frame(data);
}

int	render(t_data *data)
{
	data->plr->has_moved += move_player(data);
	if (data->plr->has_moved == 0)
		return (0);
	render_raycast(data);
	return (0);
}
