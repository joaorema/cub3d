/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/26 11:08:02 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Mylib/libft.h"
# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include <stdio.h>
# include <unistd.h>
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

//colours
# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define BLUE   "\033[1;36m"

//constants
# define TILE_SIZE 32
# define WS " \t\n\r\v\f"
# define CH_MAP "01NSEW"
# define N_CH_MAP "01NSEW \t\n\r\v\f"
# define NN_CH_MAP "01 \t\n\r\v\f"
# define NB "0123456789"
/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */
typedef struct s_map_inf
{
	char	*no_pth;
	char	*so_pth;
	char	*ea_pth;
	char	*we_pth;
	int		*f_rgb;
	int		*c_rgb;
}	t_map_inf;

typedef struct s_text
{
	void	*no;
	void	*so;
	void	*we;
	void	*ea;
}	t_text;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_ints
{
	int	i;
	int	j;
	int	x;
	int	z;
}	t_ints;

typedef struct s_gnl
{
	char	*line;
	int		fd;
}	t_gnl;

typedef struct s_rgb
{
	int	f_val;
	int	s_val;
	int	t_val;
}	t_rgb;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	char		**map;
	char		**tmp_map;
	t_map_inf	map_inf;
	t_text		*txt;
	char		player_dir;
	t_point		player_pos;
	int			map_width;
	int			map_height;
}	t_game;

/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
int		main(int ac, char *av[]);

//00_init
void	init_game(t_game *game);
void	init_gnl(t_gnl *gnl);
void	init_ints(t_ints *ints);

//01_init_imgs
void	start_wind(t_game *game);
int		close_window(void *param);

//00_parse
void	load_and_parse_map(t_game *game, char *file);
void	ch_file(t_game *game, char *file);
void	set_map_info(t_game *game, char *file);

//01_ch_map
void	set_height(t_game *game, char *file);
void	set_width_and_load(t_game *game, char *file);
void	set_width_and_load_util(t_game *game, bool *map_limit, char *line);
bool	only_ws(char *line);
void	add_line_to_map(t_game *game, char *line);

//02_ch_map_info
void	set_map_info(t_game *game, char *file);
void	set_map_info_util(t_game *game, t_gnl *gnl, int n);
int		get_pth(t_game *game, t_gnl gnl);
int		which_dir(char *line);
void	set_pth(t_game *game, t_gnl gnl, char **set_str);

//03_rgb_info
void	add_f_and_c(t_game *game, t_gnl gnl);
int		get_rgb_val(t_game *game, t_gnl gnl, int *start);
void	ch_mid_val(t_game *game, t_gnl gnl, int *i, bool *ch);
void	set_rgb_f(t_game *game, t_gnl gnl, t_rgb rgb);
void	set_rgb_c(t_game *game, t_gnl gnl, t_rgb rgb);

//04_parse_map_info
void	parse_map_info(t_game *game);
void	ch_missing_info(t_game *game);
void	ch_txt_paths(t_game *game);
void	ch_player_and_inv_chars(t_game *game);

//05_check_walls
void	ch_closed_walls(t_game *game, char **tmp_map, int max_x, int max_y);
t_point	prep_chars(char **tmp_map, int max_y, int max_x);
void	flood_fill(t_game *game, t_point start_pos, char tg);
void	ch_islands(t_game *game, char **tmp_map, int max_y, int max_x);

//06_load_utils
int		get_line_len(char *line);
int		safe_fd_open(char *file);
int		is_map(char *line);
int		empty_line(char *line);

//07_parse_utils
void	ch_dups(t_game *game, char *path, t_gnl gnl);
bool	char_is_valid(char c);
bool	play_char(char c);
void	set_pl_info(t_game *game, char c, int x, int y);

//08_check_walls_utils
void	load_tmp_map(t_game *game);
bool	ch_all_sides(t_game *game, int x, int y, char tg);
void	add_extra_line(t_game *game, t_ints *ints, int n);
void	incr_ints(int *z, int *i);

//00_close_and_free
void	print_err_and_exit(t_game *game, char *err_msg, int exit, t_gnl *gnl);
void	close_and_free(t_game *game, int exit_code);
void	free_game(t_game *game);
void	kill_visuals(t_game *game);

//debug to delete
void	print_map_info(t_game *game);
void	print_player_info(t_game *game);
void	print_tmp_map(t_game *game, int n, t_point *pos);

#endif