/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:07:30 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/11 14:51:53 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

int	count_words(char *line, char delimiter)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] == delimiter)
			i++;
		if (line[i] != '\0')
			count++;
		while (line[i] != delimiter && line[i] != '\0')
			i++;
	}
	return (count);
}

void	free_map(int **map, int allocated_rows)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < allocated_rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	**allocate_map(int width, int height)
{
	int	**map;
	int	i;

	map = (int **)malloc(sizeof(int *) * height);
	if (!map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map[i] = (int *)malloc(sizeof(int) * width);
		if (!map[i])
		{
			free_map(map, i);
			return (NULL);
		}
		i++;
	}
	return (map);
}

int	**allocate_colors(int width, int height)
{
	int	**colors;
	int	i;

	colors = (int **)malloc(sizeof(int *) * height);
	if (!colors)
		return (NULL);
	i = 0;
	while (i < height)
	{
		colors[i] = (int *)malloc(sizeof(int) * width);
		if (!colors[i])
		{
			free_map(colors, i);
			return (NULL);
		}
		i++;
	}
	return (colors);
}

void	parse_point(char *str, int *z, int *color)
{
	char	**split;

	split = ft_split(str, ',');
	*z = ft_atoi(split[0]);
	if (split[1])
		*color = ft_atoi_base(split[1], "0123456789ABCDEF");
	else
		*color = -1;
	free(split[0]);
	free(split[1]);
	free(split);
}

void	fill_map_row(int **map, int **colors, char *line, int row, int width)
{
	char	**numbers;
	int		col;

	numbers = ft_split(line, ' ');
	if (!numbers)
		return ;
	col = 0;
	while (col < width)
	{
		parse_point(numbers[col], &map[row][col], &colors[row][col]);
		free(numbers[col]);
		col++;
	}
	free(numbers);
}
