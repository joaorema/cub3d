/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/24 19:07:17 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "Mylib/libft.h"
# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
#include <stdio.h>
#include <unistd.h>
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
# define COL "Missing colour information\n"
# define RGB "Incorrect RGB info\n"
# define PTH "Incorrect path info\n"
# define TXT "Impossible to open texture\n"
# define PL "Incorrect number of players\n"
# define INV "Invalid char in map\n"

//colours
# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define BLUE   "\033[1;36m"

//constants
# define TILE_SIZE 32
# define WS " \t\n\r\v\f"
# define CH_MAP "01NSEW"
# define N_CH_MAP "01 \t\n\r\v\f"
# define NB "0123456789"
/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */
typedef struct s_position
{
    int x;
    int y;
    
} t_position;

typedef struct s_map_inf
{
	char	*no_pth;
	char	*so_pth;
	char	*ea_pth;
	char	*we_pth;
	int		*f_rgb;
	int		*c_rgb;
} t_map_inf;

typedef struct s_text
{
	void	*NO;
	void	*SO;
	void	*WE;
	void	*EA;
}	t_text;

typedef struct s_game
{
    void		*mlx;
    void		*win;
    char		**map;
    char		**tmp_map;
	t_map_inf 	map_inf;	
	t_text		*txt;
    char 		player_dir;
    int			player_x;
    int			player_y;
    int			map_width;
    int			map_height;
    
} t_game;
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
int	main(int ac, char *av[]);

//00_init
void	init_game(t_game *game);
void	start_wind(t_game *game);
int		close_window(void *param);

//00_parse
void	load_and_parse_map(t_game *game, char *file);
int		ch_file(t_game *game, char *file);
void	set_map_info(t_game *game, char *file);

//01_ch_map
void	set_height(t_game *game, char *file);
void 	set_width_and_load(t_game *game, char *file);
bool	only_ws(char *line);
void 	add_line_to_map(t_game *game, char *line);

//02_ch_map_info
void	set_map_info(t_game *game, char *file);
void	set_map_info_util(t_game *game, char **line, int fd, int n);
int 	get_pth(t_game *game, char *line);
int		which_dir(char *line);
void 	set_pth(t_game *game, char *line, char **set_str);

//03_rgb_info
void 	add_f_and_c(t_game *game, char *line);
int		get_rgb_val(t_game *game, char *line, int *start);
void	ch_mid_val(t_game *game, char c, bool *ch, int n);
void	set_rgb(t_game *game, char *line, int f_val, int s_val, int t_val);

//04_parse_map_info
void	parse_map_info(t_game *game);
void	ch_missing_info(t_game *game);
void	ch_txt_paths(t_game *game);
void	ch_player_and_inv_chars(t_game *game);
void	ch_closed_walls(t_game *game);

//05_load_utils
int		safe_fd_open(char *file);
int		is_map(char *line);
int		get_line_len(char *line);
int		empty_line(char *line);

//06_parse_utils
bool	char_is_valid(char c);
void	set_pl_info(t_game *game, char c, int x, int y);

//00_close_and_free
void	print_err_and_exit(t_game *game, char *err_msg, int exit_code);
void	close_and_free(t_game *game, int exit_code);
void	free_game(t_game *game);
void	kill_visuals(t_game *game);

//debug to delete
void	print_map_info(t_game *game);

#endif