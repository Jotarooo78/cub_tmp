/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_delimiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matis <matis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:07:16 by armosnie          #+#    #+#             */
/*   Updated: 2025/12/15 11:57:36 by matis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	count;
	int	is_delimiter;

	i = 0;
	count = 0;
	while (s[i])
	{
		is_delimiter = 0;
		if (s[i] && s[i] != c)
			i++;
		if (s[i] && s[i] == c)
		{
			is_delimiter = 1;
			count++;
			i++;
		}
	}
	if (is_delimiter == 0)
		count++;
	return (count);
}

char	*dup_with_delimiter(const char *s, char c)
{
	int		i;
	char	*dup;

	i = 0;
	if (s[i] && s[i] != c)
		while (s[i] && s[i] != c)
			i++;
	else
		i = 1;
	dup = malloc(sizeof(char) * (i + 2));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dup[i] = s[i];
		i++;
	}
	if (s[i] == c)
	{
		dup[i] = '\n';
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	**split_with_delimiter(const char *s, char c)
{
	char	**split;
	int		j;
	int		i;

	i = 0;
	j = 0;
	split = malloc(sizeof(char *) * (count_words((char *)s, c) + 1));
	if (split == NULL || s == NULL)
		return (NULL);
	while (s[i])
	{
		split[j] = dup_with_delimiter(&s[i], c);
		if (split[j++] == NULL)
			return (free_array(split), NULL);
		while (s[i] && s[i] != c)
			i++;
		if (s[i] == c)
			i++;
	}
	split[j] = NULL;
	return (split);
}
