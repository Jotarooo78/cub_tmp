/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:02:05 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/16 14:41:58 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_different_content(char **map, int i, int j)
{
	if (map[i][j] == '0')
	{
		if (map[i + 1][j] != '1' && map[i + 1][j] != '0' && map[i + 1][j] != 'N'
			&& map[i + 1][j] != 'S' && map[i + 1][j] != 'W' && map[i
			+ 1][j] != 'E')
			return (1);
		if (map[i - 1][j] != '1' && map[i - 1][j] != '0' && map[i - 1][j] != 'N'
			&& map[i - 1][j] != 'S' && map[i - 1][j] != 'W' && map[i
			- 1][j] != 'E')
			return (1);
		if (map[i][j + 1] != '1' && map[i][j + 1] != '0' && map[i][j + 1] != 'N'
			&& map[i][j + 1] != 'S' && map[i][j + 1] != 'W' && map[i][j
			+ 1] != 'E')
			return (1);
		if (map[i][j - 1] != '1' && map[i][j - 1] != '0' && map[i][j - 1] != 'N'
			&& map[i][j - 1] != 'S' && map[i][j - 1] != 'W' && map[i][j
			- 1] != 'E')
			return (1);
	}
	return (0);
}

int	check_wall(char **map)
{
	int	i;
	int	j;
	int	len;
	int line_len;

	i = 1;
	len = count_map(map);
	while (map[i] && i < len)
	{
		j = 0;
		while (skip_whitespace(map[i][j]))
			j++;
		line_len = ft_strlen(map[i]) - j;
		while (map[i][j])
		{
			if (map[len - 1][j] == '0' || map[0][j] == '0')
				return (1);
			if (is_different_content(map, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_map_char(char c)
{
	if (!c)
		return (0);
	if (c == '1')
		return (1);
	if (c == '0')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'N')
		return (1);
	if (c == 'E')
		return (1);
	if (c == 'W')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

void	transform_space_into_1(t_data *data)
{
	int	i;
	int	j;
	int	len;

	len = longest_line(data->map);
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (j < len)
		{
			if ((data->map[i][j] == ' ' || data->map[i][j] == '\0')
					&& (j > 0 && is_map_char(data->map[i][j - 1]))
					&& (j < (len - 1) && is_map_char(data->map[i][j + 1])))
				data->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	parse_map(t_data *data)
{
	data->map = dup_only_map(data);
	if (!data->map)
		return (error_2(data, "dup error\n"), 1);
	if (is_valid_char_in_map(data->map))
		return (error_2(data, "invalid character in map\n"), 1);
	if (player_position(data))
		return (error_2(data, "0 or more than 1 player\n"), 1);
	transform_space_into_1(data);
	if (check_wall(data->map))
		return (error_2(data, "invalid map format\n"), 1);
	get_map_x_y(data);
	return (0);
}
