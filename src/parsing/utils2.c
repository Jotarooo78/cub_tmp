/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:22:36 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/15 17:38:09 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	longest_line(char **map)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

void	get_map_x_y(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		if (j == 0)
			while (data->map[i][j])
				j++;
		i++;
	}
	data->map_y = i;
	data->map_x = j;
}

char	*strdup_with_longest_line(t_data *data, char *s1)
{
	int		i;
	int		len;
	char	*dup;

	len = longest_line(data->map);
	dup = (char *)malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	while (i < len)
	{
		dup[i] = '\0';
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

