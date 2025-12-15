/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 14:58:53 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/15 11:56:16 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_struct_data(t_data *data)
{
	if (!data)
		return ;
	if (data->text->no != NULL)
		free(data->text->no);
	if (data->text->so != NULL)
		free(data->text->so);
	if (data->text->we != NULL)
		free(data->text->we);
	if (data->text->ea != NULL)
		free(data->text->ea);
	if (data->text->fl != NULL)
		free(data->text->fl);
	if (data->text->ce != NULL)
		free(data->text->ce);
	if (data->map != NULL)
		free_array(data->map);
	if (data->plr != NULL)
		free(data->plr);
	if (!data->mlx)
		return ;
	destroy_graphics(data);
}

void	free_everything(t_data *data)
{
	free_struct_data(data);
	free(data->text);
	free(data);
}

void	error(t_data *data, char *str)
{
	perror(str);
	free_struct_data(data);
	free(data->text);
	free(data);
}

void	error_2(t_data *data, char *str)
{
	ft_putstr_fd(str, 2);
	free_struct_data(data);
	free(data->text);
	free(data);
}
