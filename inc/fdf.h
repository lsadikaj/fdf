/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:42:30 by lsadikaj          #+#    #+#             */
/*   Updated: 2025/12/04 11:45:12 by lsadikaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# ifdef __APPLE__
#  include "../minilibx_mms_20200219/mlx.h"
# else
#  include <X11/X.h>
#  include <X11/Xlib.h>
#  include <X11/keysym.h>
#  include "mlx.h"
# endif

# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

/* Key codes - macOS vs Linux */
# ifdef __APPLE__
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_H 4
#  define KEY_P 35
#  define KEY_PLUS 24
#  define KEY_MINUS 27
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_SPACE 49
#  define KEY_PAGEUP 116
#  define KEY_PAGEDOWN 121
# else
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_H 104
#  define KEY_P 112
#  define KEY_PLUS 65451
#  define KEY_MINUS 65453
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_SPACE 32
#  define KEY_PAGEUP 65365
#  define KEY_PAGEDOWN 65366
# endif

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define NUM_PALETTES 3
# define DEFAULT_ALTITUDE_SPHERE 0.2
# define DEFAULT_ZOOM_SPHERE 300

typedef enum e_projection
{
	PROJ_ISO,
	PROJ_SPHERE
}	t_projection;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_map_data
{
	int	**map;
	int	**colors;
	int	width;
}	t_map_data;

typedef struct s_bres
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	max_val;
	int	x;
	int	y;
	int	i;
}	t_bres;

typedef struct s_fdf
{
	void			*mlx;
	void			*win;
	t_img			img;
	int				**map;
	int				**colors;
	int				width;
	int				height;
	int				offset_x;
	int				offset_y;
	float			zoom;
	float			altitude;
	float			angle_x;
	float			angle_y;
	int				hide_lines;
	int				color_palette;
	int				needs_redraw;
	t_projection	projection_mode;
}	t_fdf;

// Parsing
void	parse_map(char *filename, t_fdf *fdf);
void	free_map(int **map, int allocated_rows);
int		**allocate_map(int width, int height);
int		**allocate_colors(int width, int height);
int		ft_atoi_base(char *str, char *base);
void	fill_map_row(t_map_data *data, char *line, int row);
void	parse_point(char *str, int *z, int *color);

// Projection
void	apply_isometric(int *x, int *y, int z);
void	apply_spherical(t_fdf *fdf, t_point *p, int x, int y);
void	apply_rotation(t_fdf *fdf, t_point *p);
void	apply_projection(t_fdf *fdf, t_point *p, int x, int y);

// Color
int		get_color(int x, int y, int z, t_fdf *fdf);
int		gradient_color(t_point p1, t_point p2, float percentage);

// Events
int		key_hook(int keycode, void *param);
int		close_window(void *param);
int		render_frame(void *param);
void	handle_movement(int keysym, t_fdf *fdf);
void	handle_transform(int keysym, t_fdf *fdf);
void	handle_rotation(int keysym, t_fdf *fdf);
void	handle_altitude(int keysym, t_fdf *fdf);
void	handle_projection(int keysym, t_fdf *fdf);
void	handle_color_palette(int keysym, t_fdf *fdf);

// Draw
void	draw_map(t_fdf *fdf);
void	draw_banner(t_fdf *fdf);
void	draw_line(t_fdf *fdf, t_point p1, t_point p2);
void	put_pixel(t_fdf *fdf, int x, int y, int color);
void	get_scaled_point(t_fdf *fdf, t_point *p, int x, int y);
void	draw_horizontal(t_fdf *fdf, int x, int y);
void	draw_vertical(t_fdf *fdf, int x, int y);

#endif
