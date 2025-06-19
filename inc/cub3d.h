/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/18 15:06:24 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "Mylib/libft.h"
#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>

# define PI 3.1415926535
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533                            //One degree in radians
# define NUM_RAYS 60
# define FOV (PI / 3)
# define ANGLE_STEP (FOV / NUM_RAYS)
# define B_DISTANCE 100000
# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define BLUE   "\033[1;36m"
# define TILE_SIZE 32


typedef struct s_rayhit
{
    float x;
    float y;
    float distance;
    float ra;
    float atan;
    float ntan;
    float ry;
    float rx;
    float xo;
    float yo;
    float px;
    float py;
    float maxhorizontal;
    float maxvertical;
    int dof;
    int mx;
    int my;
    float max_dof;
    
}   t_rayhit;

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
    float  player_dx;                                                     //player delta x
    float player_dy;                                                     //player delta y
    int  player_tile_x;
    int  player_tile_y;
    int  player_p_x;
    int  player_p_y;
    float  angle;                                                         //angle of player
    int map_width;
    int map_height;
    
} t_game;

//init folder
void start_game(t_game *game);
void init(t_game *game, char *file);
void init_raystruct(t_game *game, t_rayhit *hit);
void init_rayhit(t_rayhit *hit, t_game *game, float angle);
void load_images(t_game *game);
void load_map(t_game *game, char *file);
void render_map(t_game *game);
void render_images(t_game *game, int x, int y);
void find_player(t_game *game);
void update_game(t_game *game);
int  game_loop(t_game *game);

//parse folder
void count_width(t_game *game, char *file);
void count_height(t_game *game, char *file);

//player folder
void user_input(t_game *game);
int  player_move(t_game *game, int dx, int dy);
int	 handle_keyboard(int keycode, t_game *game);
int player_direction(int keycode, t_game *game);

//raycasting folder
void draw_line(t_game *game);
void draw_ray_line(t_game *game, float rx, float ry);
void render_rays(t_game *game);
void horizontal_check(t_game *game, t_rayhit *hit);
void vertical_check(t_game *game, t_rayhit *hit);
float distance(float ax, float ay, float bx, float by, float ang);              //hipotenusa

//utils folder
void	close_and_free(t_game *game, int exit_code);
void	free_game(t_game *game);

#endif