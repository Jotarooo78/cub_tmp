/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:02:05 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/15 11:56:51 by matis            ###   ########.fr       */
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

	i = 0;
	len = count_map(map);
	while (map[i] && i < len)
	{
		j = 1;
		while (skip_whitespace(map[i][j]))
			j++;
		while (map[i][j])
		{
			if (is_different_content(map, i, j))
				return (1);
			j++;
		}
		i++;
	}
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
			if (data->map[i][j] == ' ' || data->map[i][j] == '\0')
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
	if (check_wall(data->map))
		return (error_2(data, "invalid map format\n"), 1);
	transform_space_into_1(data);
	get_map_x_y(data);
	print_array(data->map);
	return (0);
}
