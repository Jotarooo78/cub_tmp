/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:00:00 by matis             #+#    #+#             */
/*   Updated: 2025/12/14 17:00:00 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_tex_img(t_data *data, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(data->mlx, path,
			&data->texinfo.size, &data->texinfo.size);
	if (!img->img)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putendl_fd(path, 2);
		clean_exit(data, 1);
	}
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

static int	*xpm_to_buffer(t_data *data, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;

	init_tex_img(data, &tmp, path);
	buffer = ft_calloc(data->texinfo.size * data->texinfo.size, sizeof(int));
	if (!buffer)
		clean_exit(data, 1);
	y = 0;
	while (y < data->texinfo.size)
	{
		x = 0;
		while (x < data->texinfo.size)
		{
			buffer[y * data->texinfo.size + x]
				= tmp.addr[y * data->texinfo.size + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(data->mlx, tmp.img);
	return (buffer);
}

static void	init_hex_colors(t_data *data)
{
	data->hex_floor = (data->text->fl->r << 16)
		| (data->text->fl->g << 8) | data->text->fl->b;
	data->hex_ceiling = (data->text->ce->r << 16)
		| (data->text->ce->g << 8) | data->text->ce->b;
}

void	init_textures(t_data *data)
{
	data->texinfo.size = TEX_SIZE;
	data->textures = ft_calloc(5, sizeof(int *));
	if (!data->textures)
		clean_exit(data, 1);
	data->textures[NORTH] = xpm_to_buffer(data, data->text->no);
	data->textures[SOUTH] = xpm_to_buffer(data, data->text->so);
	data->textures[EAST] = xpm_to_buffer(data, data->text->ea);
	data->textures[WEST] = xpm_to_buffer(data, data->text->we);
	init_hex_colors(data);
}
