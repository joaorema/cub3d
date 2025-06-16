/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/10 16:30:22 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "Mylib/libft.h"
#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <unistd.h>

# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define BLUE   "\033[1;36m"
# define TILE_SIZE 32


typedef struct s_position
{
    int x;
    int y;
    
} t_position;

typedef struct s_game
{
    void *mlx;
    void *win;
    void *player_img;
    void *wall;
    char *addr;
    char **map;
    char **temp_map;
    int  player;
    int  player_x;
    int  player_y;
    int map_width;
    int map_height;
    
} t_game;

//functions
t_game  start_game(t_game *game);

//parse
void count_width(t_game *game, char *file);
void count_height(t_game *game, char *file);
void load_images(t_game *game);
int	 handle_keyboard(int keycode, t_game *game);
void player_move(t_game *game, int dx, int dy);
void	user_input(t_game *game);
void update_player(t_game *game);
void load_map(t_game *game, char *file);
void render_map(t_game *game);
void render_images(t_game *game, int x, int y);
void update_game(t_game *game);
void find_player(t_game *game);

#endif