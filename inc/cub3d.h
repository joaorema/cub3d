/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/21 12:30:24 by joaorema         ###   ########.fr       */
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
# define RED    0x00FF0000
# define GREEN  0x0000FF00
# define BLUE   0x000000FF
# define BRICKRED 0xB22222
# define DARKGRAY 0x00333333
# define GRAY     0xFFD3D3D3
# define SKY    GRAY
# define FLOOR  DARKGRAY
# define TILE_SIZE 64

typedef struct s_image
{
    void *img;
    char *addr;
    int width;
    int height;
    int bits_per_pixel;
    int line_len;
    int x;
    int y;  
    int endian;
    
}   t_image;

typedef struct s_wall
{
    float wall_dist;
    float lineh;
    float wall_top;
    float wall_bottom;
    float screen_center;
    float hit_x;
    float hit_y;
    int y;
    int w;
    int screen_x;
    int slice_width;
    int was_hit_vertical;

}   t_wall;

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
    float max_dof;
    int dof;
    int mx;
    int my;
    
}   t_rayhit;

typedef struct s_player
{
    int  player;
    int  player_x;
    int  player_y;
    float  player_dx;                                                     //player delta x
    float player_dy;                                                     //player delta y
    int  player_tile_x;
    int  player_tile_y;
    int  player_p_x;
    int  player_p_y;

}   t_player;

typedef struct s_point
{
    float x;
    float y;
    
} t_point;

typedef struct s_game
{
    void *mlx;
    void *win;
    char **map;
    t_player player;
    t_image img;
    float  angle;                                                         //angle of player
    int map_width;
    int map_height;
    int win_width;
    int win_height;
    int key_w;
    int key_a;
    int key_s;
    int key_d;
    int key_left;
    int key_right;
    
} t_game;

//init folder
void start_game(t_game *game);
void init(t_game *game, char *file);
void init_raystruct(t_game *game, t_rayhit *hit);
void init_rayhit(t_rayhit *hit, t_game *game, float angle);
void load_map(t_game *game, char *file);
void render_map(t_game *game);
void find_player(t_game *game);
int  game_loop(t_game *game);

//parse folder
void count_width(t_game *game, char *file);
void count_height(t_game *game, char *file);

//player folder
void user_input(t_game *game);
int player_move(t_game *game, float m_x, float m_y);
int	 handle_keyboard(int keycode, t_game *game);
int player_direction(int keycode, t_game *game);

//raycasting folder
void render_rays(t_game *game);
void horizontal_check(t_game *game, t_rayhit *hit);
void vertical_check(t_game *game, t_rayhit *hit);
float distance(float ax, float ay, float bx, float by, float ang);              //hipotenusa
void render_wall(t_game *game, float angle, int col);
void init_wall(t_game *game, t_rayhit *vhit, t_rayhit *hhit, t_wall *wall);
void h_sides(t_game *game, t_rayhit *hit);
void h_up(t_game *game, t_rayhit *hit, float atan);
void h_down(t_game *game, t_rayhit *hit, float atan);
void update_hcheck(t_rayhit *hit);
void final_hupdate(t_rayhit *hit);
void hhit_wall(t_rayhit *hit, float ra);
void h_s_tile(t_rayhit *hit);
void v_top_down(t_game *game, t_rayhit *hit);
void v_right(t_game *game, t_rayhit *hit, float ntan);
void v_left(t_game *game, t_rayhit *hit, float ntan);
void update_vcheck(t_rayhit *hit);
void final_vupdate(t_rayhit *hit);
void vhit_wall(t_rayhit *hit, float ra);
void v_s_tile(t_rayhit *hit);
void draw_topbottom(t_game *game, t_wall *wall);

//utils folder
void	close_and_free(t_game *game, int exit_code);
void	free_game(t_game *game);
int     get_texture_pixel(t_image *texture, int x, int y);
void my_mlx_pixel_put(t_image *img, int x, int y, int color);

#endif