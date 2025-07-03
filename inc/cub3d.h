/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/07/03 09:31:13 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Mylib/libft.h"
# include "mlx_linux/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdbool.h>

/* ************************************************************************** */
/*                                    MACROS                                  */
/* ************************************************************************** */
//error messages
# define ERR "Error\n"
# define USG "Usage: ./cub3d <map_file> \n"
# define OP "Unable to open file\n"
# define EXT "File extension should be .cub\n"
# define EMPT "Empty file or unable to read\n"
# define MINF "Missing info on map\n"
# define WINF "Wrong info on map\n"
# define MMAP "Missing map\n"
# define COL "Missing color information\n"
# define RGB "Incorrect RGB info\n"
# define PTH "Incorrect path info\n"
# define TXT "Impossible to open texture\n"
# define PL "Incorrect number of players\n"
# define INV "Invalid char in map\n"
# define INVMAP "Map is invalid\n"
# define INFAFTMAP "Information after map is invalid\n"
# define OPMAP "Map has an open end\n"
# define SPMAP "Space in map\n"
# define DPINF "Duplicate info on map\n"
# define FD "Unable to create file descriptor\n"

//colors
# define RESET	"\033[0m"
# define RED	"\033[1;31m"
# define GREEN	"\033[1;32m"
# define BLUE	"\033[1;36m"

//keycodes
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

//constants
# define PI			3.1415926535
# define P2			1.57079632675
# define P3			4.71238898025
# define NORTH		0
# define SOUTH		1
# define WEST		2
# define EAST		3
# define WS			" \t\n\r\v\f"
# define CH_MAP		"01NSEW"
# define N_CH_MAP	"01NSEW \t\n\r\v\f"
# define NB			"0123456789"

//game settings
# define WIDTH		800
# define HEIGHT		800
# define NUM_RAYS	WIDTH
# define FOV		1.0471975512 
# define ANGLE_STEP	0.001309
# define B_DISTANCE	1000000
# define TILE_SIZE	32
# define P_RADIUS	6.4f
# define ROT_SPEED	0.02f
# define MOVE_SPEED	03.0f

//structs
typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
}	t_keys;

typedef struct s_map_inf
{
	char		*no_pth;
	char		*so_pth;
	char		*ea_pth;
	char		*we_pth;
	int			*f_rgb;
	int			*c_rgb;
}	t_map_inf;

typedef struct s_ints
{
	int			i;
	int			j;
	int			x;
	int			z;
}	t_ints;

typedef struct s_gnl
{
	char		*l;
	int			fd;
}	t_gnl;

typedef struct s_text
{
	void		*no;
	void		*so;
	void		*we;
	void		*ea;
}	t_text;

typedef struct s_rgb
{
	int			f_val;
	int			s_val;
	int			t_val;
}	t_rgb;

typedef struct s_point
{
	float		x;
	float		y;
}	t_point;

typedef struct s_pl
{
	int			x;
	int			y;
}	t_pl;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_len;
	int			endian;
	t_point		pos;
}	t_image;

typedef struct s_wall
{
	int			texture_x;
	int			screen_x;
	int			slice_width;
	int			hit_vertical;
	float		ray_angle;
	float		distance;
	float		projected_height;
	float		top_pixel;
	float		bottom_pixel;
	float		screen_center_y;
	int			side;
	t_point		hit_point;
}	t_wall;

typedef struct s_rayhit
{
	int			depth_of_field;
	int			map_x;
	int			map_y;
	float		distance;
	float		ray_angle;
	float		atan_angle;
	float		ntan_angle;
	float		next_ray_y;
	float		next_ray_x;
	float		x_offset;
	float		y_offset;
	float		max_horizontal;
	float		max_vertical;
	float		max_depth_of_field;
	t_point		hit_pos;
	t_point		player_pos;
}	t_rayhit;

typedef struct s_rayhits
{
	t_rayhit	v_hit;
	t_rayhit	h_hit;
}	t_rayhits;

typedef struct s_player
{
	int			tile_x;
	int			tile_y;
	t_point		delta;
	t_point		position;
	t_point		pixel_offset;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			map_width;
	int			map_height;
	int			win_width;
	int			win_height;
	t_keys		keys;
	char		**map;
	char		**tmp_map;
	char		player_direction;
	float		player_angle;
	int			floor_color;
	int			sky_color;
	t_map_inf	map_inf;
	t_text		*txt;
	t_player	player;
	t_image		img;
	t_image		no_img;
	t_image		so_img;
	t_image		we_img;
	t_image		ea_img;
}	t_game;

//CLOSE//
//00_close_and_free.c
void			print_err_and_exit(t_game *game, char *err_msg,
					int exit, t_gnl *gnl);
void			free_game(t_game *game);
void			kill_visuals(t_game *game);
void			close_and_free(t_game *game, int exit_code);
int				close_x(void *param);

//01_kill_visuals.c
void			kill_visuals(t_game *game);
void			destroy_imgs(t_game *game);

//INIT//
//00_init_struct.c
void			init_game_struct(t_game *game);
void			init_images(t_game *game);
void			init_map(t_game *game);
void			init_player(t_game *game);
void			init_keys(t_game *game);

//01_init_hit.c
void			init_raystruct(t_game *game, t_rayhit *hit);
void			init_rayhit(t_rayhit *hit, t_game *game, float angle);

//02_init_wall.c
void			init_wall(t_game *game, t_rayhits *hits,
					t_wall *wall, float angle);
void			clamp_wall(t_game *game, t_wall *wall);
void			set_wall(t_wall *wall);
void			check_hit(t_wall *wall, float *angle, float *offset);
void			check_distance(t_rayhit *vhit, t_rayhit *hhit, t_wall *wall);

//03_init_game_loop.c
void			init(t_game *game, char *file);
void			render_map(t_game *game);
int				game_loop(t_game *game);
void			handle_keys(t_game *game);
void			loop(t_game *game);

//04_init_utils.c
void			init_gnl(t_gnl *gnl);
void			init_ints(t_ints *ints);

//PARSE//
//00_load_and_parse.c
void			load_and_parse_map(t_game *game, char *file);
void			ch_file(t_game *game, char *file);

//01_ch_map
void			set_height(t_game *game, char *file);
void			set_width_and_load(t_game *game, char *file);
void			set_width_and_load_util(t_game *game, bool *map_limit,
					char *line);
bool			only_ws(char *line);
void			add_line_to_map(t_game *game, char *line);

//02_ch_map_info
void			set_map_info(t_game *game, char *file);
void			set_map_info_util(t_game *game, t_gnl *gnl, int n);
int				get_pth(t_game *game, t_gnl gnl);
int				which_dir(char *line);
void			set_pth(t_game *game, t_gnl gnl, char **set_str);

//03_rgb_info
void			add_f_and_c(t_game *game, t_gnl gnl);
int				get_rgb_val(t_game *game, t_gnl gnl, int *start);
void			ch_mid_val(t_game *game, t_gnl gnl, int *i, bool *ch);
void			set_rgb_f(t_game *game, t_gnl gnl, t_rgb rgb);
void			set_rgb_c(t_game *game, t_gnl gnl, t_rgb rgb);

//04_parse_map_info
void			parse_map_info(t_game *game);
void			ch_missing_info(t_game *game);
void			ch_txt_paths(t_game *game);
void			ch_player_and_inv_chars(t_game *game);

//05_check_walls
void			ch_closed_walls(t_game *game, char **tmp_map,
					int max_x, int max_y);
t_pl			prep_chars(char **tmp_map, int max_y, int max_x);
void			flood_fill(t_game *game, t_pl start_pos, char tg);
void			ch_islands(t_game *game, char **tmp_map, int max_y, int max_x);

//06_load_utils
int				gll(char *line);
int				safe_fd_open(char *file);
int				is_map(char *line);
int				empty_line(char *line);

//07_parse_utils
void			ch_dups(t_game *game, char *path, t_gnl gnl);
bool			char_is_valid(char c);
bool			play_char(char c);
void			set_pl_info(t_game *game, char c, int x, int y);

//08_check_walls_utils
void			load_tmp_map(t_game *game);
void			add_extra_line(t_game *game, t_ints *ints, int n);
void			incr_ints(int *z, int *i);
bool			ch_all_sides(t_game *game, int x, int y, char tg);

//PLAYER//
//00_player.c
int				handle_keyboard(int keycode, t_game *game);
int				key_released(int keycode, t_game *game);
int				player_direction(int keycode, t_game *game);
int				player_move(t_game *game, float m_x, float m_y);
void			rotate_player(t_game *game, float rotation);

//01_player_utils.c
void			find_player(t_game *game);
void			set_player_angle(t_game *game, char dir);
void			set_player_start(t_game *game, int x, int y, char dir);
int				is_walkable(t_game *game, float x, float y);
int				move_player(t_game *game);

//RAYCASTING
//00_raycasting_init.c
void			horizontal_check(t_game *game, t_rayhit *hit);
void			vertical_check(t_game *game, t_rayhit *hit);

//01_horizontal_variables.c
void			h_sides(t_game *game, t_rayhit *hit);
void			h_up(t_game *game, t_rayhit *hit, float atan);
void			h_down(t_game *game, t_rayhit *hit, float atan);
void			update_vcheck(t_rayhit *hit);
void			final_hupdate(t_rayhit *hit);

//02_horizontal_variables_utils.c
void			hhit_wall(t_rayhit *hit);
void			h_s_tile(t_rayhit *hit);

//03_vertical_variables.c
void			v_top_down(t_game *game, t_rayhit *hit);
void			v_right(t_game *game, t_rayhit *hit, float ntan);
void			v_left(t_game *game, t_rayhit *hit, float ntan);
void			update_hcheck(t_rayhit *hit);
void			final_vupdate(t_rayhit *hit);

//04_vertical_variables_utils.c
void			vhit_wall(t_rayhit *hit);
void			v_s_tile(t_rayhit *hit);

//05_textures.c
void			load_wall_images(t_game *game);
unsigned int	get_texture(t_game *game, t_wall *wall, int y);
t_image			*set_side(t_game *game, t_wall *wall);

//06_render.c
void			render_rays(t_game *game);
void			render_wall(t_game *game, float angle, int col);
void			draw_topbottom(t_game *game, t_wall *wall);
void			draw_wall_slice(t_game *game, t_wall *wall);
int				create_trgb(int r, int g, int b);

//07_utils.c
float			distance(float ax, float ay, float bx, float by);
float			clamptexture(float value, float min, float max);
int				clamp_point(int value, int min, int max);
void			my_mlx_pixel_put(t_image *img, int x, int y, int color);
void			draw(t_image *image, t_point pos, t_point size, int color);

//debugg
void			print_map_info(t_game *game);
void			print_player_info(t_game *game);
void			print_tmp_map(t_game *game, int n, t_pl *pos);

#endif
