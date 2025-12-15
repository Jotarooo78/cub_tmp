/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:16:55 by messengu          #+#    #+#             */
/*   Updated: 2025/12/15 12:25:13 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	destroy_texture_img(t_data *data, t_img **slot)
{
	if (!slot || !*slot)
		return ;
	if ((*slot)->img)
		mlx_destroy_image(data->mlx, (*slot)->img);
	free(*slot);
	*slot = NULL;
}

void	destroy_textures(t_data *data)
{
	if (!data || !data->text)
		return ;
	if (data->text->no)
		free(data->text->no);
	if (data->text->so)
		free(data->text->so);
	if (data->text->ea)
		free(data->text->ea);
	if (data->text->we)
		free(data->text->we);
	if (data->text->fl)
		free(data->text->fl);
	if (data->text->ce)
		free(data->text->ce);
	free(data->text);
	data->text = NULL;
}

void	destroy_graphics(t_data *data)
{
	if (!data)
		return ;
	destroy_textures(data);
	if (data->win)
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
	if (data->plr)
	{
		free(data->plr);
		data->plr = NULL;
	}
}
