/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/19 14:51:19 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "Mylib/libft.h"
#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <unistd.h>

/* ************************************************************************** */
/*                                    MACROS                                  */
/* ************************************************************************** */
//error messages
# define ERR "Error\n"
# define USG "Usage: ./cub3d <map_file> \n"
# define OP "Unable to open file\n"
# define EXT "File extension should be .cub\n"
# define EMPT "Empty file or unable to read\n"

//colors
# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define BLUE   "\033[1;36m"

//constants
# define WS " \t\n\r\v\f"
# define CH_MAP "01NSEW"
# define N_CH_MAP "01 \t\n\r\v\f"
/* ************************************************************************** */
/*                                   STRUCTS                                  */
/* ************************************************************************** */
typedef struct s_position
{
    int x;
    int y;
    
} t_position;

typedef struct s_game
{
    void	*mlx;
    void	*win;
    char	**map;
    char	**tmp_map;
    int 	player;
    int		player_x;
    int		player_y;
    int		map_width;
    int		map_height;
    
} t_game;
/* ************************************************************************** */
/*                                 PROTOTYPES                                 */
/* ************************************************************************** */
int main(int ac, char *av[]);

//init
void  init_game(t_game *game);

//parse
void	ch_and_load_map(t_game *game, char *file);
int		ch_file(t_game *game, char *file);
void	set_width_and_load(t_game *game, char *file);
void	add_line_to_map(t_game *game, char *file);

//parse_utils
int		get_line_len(char *line);
void	set_height(t_game *game, char *file);
int		safe_fd_open(char *file);
int		is_map(char *line);

//close
void	close_and_free(t_game *game, int exit_code);
void	free_game(t_game *game);

#endif