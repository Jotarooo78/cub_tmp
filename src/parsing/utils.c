/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:19:11 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/15 11:57:50 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_ext(char *file, char *ext)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (1);
	if (ft_strncmp(&file[len - 4], ext, 4) == 0)
		return (0);
	return (1);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
	printf("\n");
}

int	skip_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	count_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	is_valid_char_in_map(char **map)
{
	char	*trimmed;
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		trimmed = ft_strtrim(map[i], " \t\n");
		if (!trimmed)
			return (1);
		j = 0;
		while (trimmed[j])
		{
			if (trimmed[j] != '1' && trimmed[j] != '0' && trimmed[j] != 'N'
				&& trimmed[j] != 'S' && trimmed[j] != 'W' && trimmed[j] != 'E'
				&& trimmed[j] != ' ')
				return (free(trimmed), 1);
			j++;
		}
		free(trimmed);
		i++;
	}
	return (0);
}
