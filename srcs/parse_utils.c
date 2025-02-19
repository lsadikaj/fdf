/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:07:30 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/19 14:52:46 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

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
	int		i;

	split = ft_split(str, ',');
	if (!split)
		return ;
	*z = ft_atoi(split[0]);
	if (split[1])
		*color = ft_atoi_base(split[1], "0123456789ABCDEF");
	else
		*color = -1;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	fill_map_row(t_map_data *data, char *line, int row)
{
	char	**numbers;
	int		col;
	int		z;
	int		color;

	numbers = ft_split(line, ' ');
	if (!numbers)
		return ;
	col = 0;
	while (numbers[col] && col < data->width)
	{
		parse_point(numbers[col], &z, &color);
		data->map[row][col] = z;
		data->colors[row][col] = color;
		free(numbers[col]);
		col++;
	}
	while (numbers[col])
	{
		free(numbers[col]);
		col++;
	}
	free(numbers);
}
