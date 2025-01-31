/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:29:37 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/01/31 15:35:36 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

static int	get_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

static int	get_width(char *filename)
{
	int		fd;
	int		width;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	line = get_next_line(fd);
	if (!line)
		return (-1);
	width = count_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}

static int	**allocate_map(int width, int height)
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
			return (NULL);
		i++;
	}
	return (map);
}

static void	fill_map(int **map, char *filename, int width)
{
	int 	fd;
	int		row;
	int		col;
	char	*line;
	char	**numbers;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	row = 0;
	while ((line = get_next_line(fd)) && row < width)
	{
		numbers = ft_split(line, ' ');
		col = 0;
		while (col < width)
		{
			//ft_printf("x: %d, y: %d, z:= %d\n", col, row, ft_atoi(numbers[col]));
			map[row][col] = ft_atoi(numbers[col]);
			free(numbers[col]);
			col++;
		}
		free(numbers);
		free(line);
		row++;
	}
	close(fd);
}

void	parse_map(char *filename, t_fdf *fdf)
{
	fdf->height = get_height(filename);
	if (fdf->height <= 0)
		return ;
	fdf->width = get_width(filename);
	if (fdf->width <= 0)
		return ;
	fdf->map = allocate_map(fdf->width, fdf->height);
	if (!fdf->map)
		return ;
	fill_map(fdf->map, filename, fdf->width);
}
