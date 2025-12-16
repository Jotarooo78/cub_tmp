/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:27:44 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/16 12:35:48 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	detect_features(char **map)
{
	int		i;
	int		end;
	int		count;
	char	*trimmed;

	i = 0;
	end = 0;
	count = 0;
	while (map[i])
	{
		trimmed = ft_strtrim(map[i], " \t\n");
		if (!trimmed)
			return (-1);
		if (trimmed[0] == 'N' || trimmed[0] == 'S' || trimmed[0] == 'W'
			|| trimmed[0] == 'E' || trimmed[0] == 'F' || trimmed[0] == 'C')
			count++;
		free(trimmed);
		if (count < 6)
			end++;
		i++;
	}
	if (count == 6)
		return (end + 1);
	return (-1);
}

char	**transform_array(char *line)
{
	char	*formate_line;
	char	**split;

	formate_line = ft_strtrim(line, " \t\n");
	if (!formate_line)
		return (NULL);
	split = ft_split(formate_line, ' ');
	if (!split || !split[0] || !split[1] || split[2])
		return (free_array(split), free(formate_line), NULL);
	free(formate_line);
	return (split);
}

int	manage_features(t_data *data)
{
	int		i;
	char	**split;
	int		ret;
	int		len;

	i = -1;
	len = detect_features(data->map);
	if (len == -1)
		return (1);
	while (++i < len)
	{
		split = transform_array(data->map[i]);
		if (!split)
			return (1);
		ret = check_features(split[0]);
		if (ret >= 0)
		{
			if (ifi(data, ret) || ifd(data, split, ret) != 0)
				return (free_array(split), 1);
		}
		else
			return (free_array(split), 1);
		free_array(split);
	}
	return (0);
}

char	*join_map(char *str, int fd)
{
	char	*new_tmp;
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
		return (NULL);
	while (str)
	{
		new_tmp = ft_strjoin(tmp, str);
		if (!new_tmp)
			return (free(str), free(tmp), close(fd), NULL);
		free(tmp);
		tmp = new_tmp;
		free(str);
		if (ft_strlen(tmp) > 10000)
			return (free(tmp), close(fd), NULL);
		str = get_next_line(fd);
	}
	close(fd);
	return (tmp);
}

int	parse(t_data *data, char *file)
{
	int		fd;
	char	*str;
	char	*join;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error(data, "fd error"), 1);
	str = get_next_line(fd);
	join = join_map(str, fd);
	if (join == NULL)
		return (error_2(data, "join error\n"), 1);
	data->map = split_with_delimiter(join, '\n');
	if (!data->map || is_valid_map(data->map))
		return (free(join), error_2(data, "invalid map format\n"), 1);
	free_array(data->map);
	data->map = ft_split(join, '\n');
	if (!data->map)
		return (free(join), error_2(data, "split error\n"), 1);
	free(join);
	if (manage_features(data))
		return (error_2(data, "invalid features\n"), 1);
	if (parse_map(data))
		return (1);
	return (0);
}
