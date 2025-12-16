/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messengu <messengu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:43:48 by matis             #+#    #+#             */
/*   Updated: 2025/12/16 10:57:54 by messengu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../src/utils/libft/libft.h"
# include "../src/utils/libx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <unistd.h>

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK 1L
# define KEY_RELEASE_MASK 2L
# define DESTROY_NOTIFY 17
# define NO_EVENT_MASK 0L

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define TEX_SIZE 64

# define MOVESPEED 0.05
# define ROTSPEED 0.02

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

// ---- STRUCTS ----
typedef struct s_color
{
	int				r;
	int				g;
	int				b;

}					t_color;

/**
 * @brief Holding data for directions.
 * @param no North
 * @param s
 */
typedef struct s_text
{
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	t_color			*fl;
	t_color			*ce;

}					t_text;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	int				has_moved;
	int				move_x;
	int				move_y;
	int				rotate;
}					t_player;

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			wall_dist;
	double			wall_x;
	int				step_x;
	int				step_y;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_texinfo
{
	int				size;
	int				index;
	int				x;
	int				y;
	double			step;
	double			pos;
}					t_texinfo;

typedef struct s_img
{
	void			*img;
	int				*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	char			**map;
	int				map_y;
	int				map_x;
	int				p_x;
	int				p_y;
	char			player;
	t_text			*text;
	t_player		*plr;
	t_ray			ray;
	t_texinfo		texinfo;
	int				**textures;
	int				**tex_pixels;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
}					t_data;

// ---- FUNCTIONS ----

// main
int					parse(t_data *data, char *file);

// parse map
int					parse_map(t_data *data);
int					start_of_map(char **map);
int					is_valid_map(char **map);
int					player_position(t_data *data);
char				**dup_only_map(t_data *data);

// parse text color
int					detect_features(char **map);

// check
int					ifi(t_data *data, int ret);
int					check_features(char *str);
int					init_color(t_text *text, char *path, int ret);
int					ifd(t_data *data, char **split, int ret);

// error
void				free_array(char **array);
void				error(t_data *data, char *str);
void				error_2(t_data *data, char *str);
void				free_everything(t_data *data);

// utils : split with delimiter
char				**split_with_delimiter(const char *s, char c);

// utils
long				ft_atol(const char *str);
int					check_ext(char *file, char *ext);
void				print_array(char **array);
int					skip_whitespace(char c);
int					is_valid_char_in_map(char **map);
int					count_map(char **map);
int					longest_line(char **map);
void				get_map_x_y(t_data *data);
char				*strdup_with_longest_line(t_data *data, char *s1);
void				destroy_graphics(t_data *data);
int					check_trimmed(char *trimmed);

// init
int					init_game_data(t_data *data);

// raycasting
void				init_ray(t_ray *ray);
int					raycasting(t_data *data);

// render
int					render(t_data *data);
void				render_frame(t_data *data);
void				set_image_pixel(t_img *image, int x, int y, int color);

// texture
void				init_textures(t_data *data);
void				init_tex_pixels(t_data *data);
void				update_tex_pixels(t_data *data, t_ray *ray, int x);

// player
void				init_player(t_data *data);
int					move_player(t_data *data);
int					rotate_player(t_data *data, double rotdir);
int					validate_move(t_data *data, double new_x, double new_y);

// input
void				listen_for_input(t_data *data);

// exit
void				clean_exit(t_data *data, int code);
int					quit_cub3d(t_data *data);
void				free_tab(void **tab);

#endif
