/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 14:11:56 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/16 11:52:38 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ifi(t_data *data, int ret)
{
	if (!data || !data->text)
		return (0);
	if (ret == 1 && data->text->no)
		return (1);
	else if (ret == 2 && data->text->so)
		return (1);
	else if (ret == 3 && data->text->we)
		return (1);
	else if (ret == 4 && data->text->ea)
		return (1);
	else if (ret == 5 && data->text->fl->r && data->text->fl->g
		&& data->text->fl->b)
		return (1);
	else if (ret == 6 && data->text->ce->r && data->text->ce->g
		&& data->text->ce->b)
		return (1);
	return (0);
}

int	check_features(char *str)
{
	if (!ft_strcmp("NO", str))
		return (1);
	if (!ft_strcmp("SO", str))
		return (2);
	if (!ft_strcmp("WE", str))
		return (3);
	if (!ft_strcmp("EA", str))
		return (4);
	if (!ft_strcmp("F", str))
		return (5);
	if (!ft_strcmp("C", str))
		return (6);
	if (!ft_strcmp(" ", str))
		return (7);
	return (-1);
}

int	is_dup_failed(t_data *data, int ret)
{
	if (ret == 1 && !data->text->no)
		return (1);
	if (ret == 2 && !data->text->so)
		return (1);
	if (ret == 3 && !data->text->we)
		return (1);
	if (ret == 4 && !data->text->ea)
		return (1);
	if (ret == 5 && !data->text->fl)
		return (1);
	if (ret == 6 && !data->text->ce)
		return (1);
	return (0);
}

int	ifd(t_data *data, char **split, int ret)
{
	if (ret == 1)
		if (!check_ext(split[1], ".xpm"))
			data->text->no = ft_strdup(split[1]);
	if (ret == 2)
		if (!check_ext(split[1], ".xpm"))
			data->text->so = ft_strdup(split[1]);
	if (ret == 3)
		if (!check_ext(split[1], ".xpm"))
			data->text->we = ft_strdup(split[1]);
	if (ret == 4)
		if (!check_ext(split[1], ".xpm"))
			data->text->ea = ft_strdup(split[1]);
	if (ret == 5)
		if (init_color(data->text, split[1], ret) == 1)
			return (1);
	if (ret == 6)
		if (init_color(data->text, split[1], ret) == 1)
			return (1);
	if (is_dup_failed(data, ret) == 1)
		return (1);
	return (0);
}
