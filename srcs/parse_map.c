/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:29:37 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/02/11 15:33:48 by lsadikaj         ###   ########.fr       */
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

static void	fill_map(int **map, int **colors, char *filename, int width)
{
	int		fd;
	int		row;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	row = 0;
	line = get_next_line(fd);
	while (line && row < width)
	{
		fill_map_row(map, colors, line, row, width);
		free(line);
		line = get_next_line(fd);
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
	fdf->colors = allocate_colors(fdf->width, fdf->height);
	if (!fdf->map || !fdf->colors)
	{
		free_map(fdf->map, fdf->height);
		free_map(fdf->colors, fdf->height);
		return ;
	}
	fill_map(fdf->map, fdf->colors, filename, fdf->width);
}
