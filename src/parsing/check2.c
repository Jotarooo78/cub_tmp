/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:08:13 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/16 12:31:32 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_color_2(t_text *text, char **split_path, char *texture)
{
	if (ft_strcmp(texture, "floor") == 0)
	{
		text->fl->r = ft_atol(split_path[0]);
		text->fl->g = ft_atol(split_path[1]);
		text->fl->b = ft_atol(split_path[2]);
		if (!(text->fl->r >= 0 && text->fl->r <= 255 && text->fl->g >= 0
				&& text->fl->g <= 255 && text->fl->b >= 0
				&& text->fl->b <= 255))
			return (1);
	}
	else if (ft_strcmp(texture, "celing") == 0)
	{
		text->ce->r = ft_atol(split_path[0]);
		text->ce->g = ft_atol(split_path[1]);
		text->ce->b = ft_atol(split_path[2]);
		if (!(text->ce->r >= 0 && text->ce->r <= 255 && text->ce->g >= 0
				&& text->ce->g <= 255 && text->ce->b >= 0
				&& text->ce->b <= 255))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	init_color(t_text *text, char *path, int ret)
{
	char	**split_path;

	split_path = ft_split(path, ',');
	if (!split_path || !split_path[0] || !split_path[1] || !split_path[2])
		return (free_array(split_path), printf("Wrong color set\n"), 1);
	if (split_path[3])
		return (free_array(split_path), printf("Wrong color set\n"), 1);
	if (ret == 5)
	{
		if (init_color_2(text, split_path, "floor") == 1)
			return (free_array(split_path), printf("Wrong color set\n"), 1);
	}
	else if (ret == 6)
	{
		if (init_color_2(text, split_path, "celing") == 1)
			return (free_array(split_path), printf("Wrong color set\n"), 1);
	}
	free_array(split_path);
	return (0);
}
