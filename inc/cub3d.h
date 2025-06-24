/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/24 13:37:31 by joaorema         ###   ########.fr       */
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
# define SKY    0xFFADD8E6
# define FLOOR  DARKGRAY
# define TILE_SIZE 128
#define KEY_ESC     65307
#define KEY_W       119
#define KEY_A       97
#define KEY_S       115
#define KEY_D       100
#define KEY_LEFT    65361
#define KEY_RIGHT   65363
#define MOVE_SPEED  35.0f

typedef struct s_point
{
    float x;
    float y;
    
} t_point;

typedef struct s_image
{
    void *img;
    char *addr;
    int width;
    int height;
    int bits_per_pixel;
    int line_len;
    int endian;
    t_point pos;
    
}   t_image;

typedef struct s_wall
{
    float distance;                                 // Distance from player to wall hit
    float projected_height;                         // Height of wall slice to draw on screen
    float top_pixel;                                // Screen y-coordinate for top of wall slice
    float bottom_pixel;                             // Screen y-coordinate for bottom of wall slice
    float screen_center_y;                          // Vertical center of screen (win_height/2)
    int texture_x;                                  // X coordinate on wall texture to sample
    int screen_x;                                   // X coordinate on screen to draw slice
    int slice_width;                                // Width of the vertical slice of the wall
    int hit_vertical;                               // Boolean: did the ray hit a vertical wall?
    t_point hit_point;                              // Coordinates where ray hit the wall

}   t_wall;

typedef struct s_rayhit
{
    t_point hit_pos;                                // Coordinates where the ray hits something
    float distance;                                 // Distance from player to hit point
    float ray_angle;                                // Angle of the current ray
    float atan_angle;                               // Auxiliary values for raycasting calculations
    float ntan_angle;
    float next_ray_y;                               // Next intersection Y coordinate for checking grid
    float next_ray_x;                               // Next intersection X coordinate for checking grid
    float x_offset;                                 // Step increment X for ray movement
    float y_offset;                                 // Step increment Y for ray movement
    t_point player_pos;                             // Player's current position
    float max_horizontal;                           // Max horizontal distance limit for ray
    float max_vertical;                             // Max vertical distance limit for ray
    float max_depth_of_field;                       // Max steps before raycasting stops
    int depth_of_field;                             // Current depth of field (number of checks)
    int map_x;                                      // Map grid X coordinate of hit
    int map_y;                                      // Map grid Y coordinate of hit
    
} t_rayhit;

typedef struct s_player
{
    int tile_x;               // Player tile/grid X coordinate
    int tile_y;               // Player tile/grid Y coordinate
    t_point delta;            // Movement delta per frame (dx, dy)
    t_point position;         // Player world coordinates (x, y)
    t_point pixel_offset;     // Pixel offset within current tile

}   t_player;


typedef struct s_game
{
    void *mlx;
    void *win;
    char **map;
    float player_angle;       // Player looking angle in radians
    int map_width;            // Width of the map in tiles
    int map_height;           // Height of the map in tiles
    int win_width;            // Window width in pixels
    int win_height;           // Window height in pixels
    int key_w;
    int key_a;
    int key_s;
    int key_d;
    int key_left;
    int key_right;
    t_player player;
    t_image img;              // Main rendering image buffer
    t_image wall_img;         // Wall texture image
    
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
void init_wall(t_game *game, t_rayhit *vhit, t_rayhit *hhit, t_wall *wall, float angle);
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
void	draw(t_image *image, t_point pos, t_point size, int color);
void draw_wall_slice(t_game *game, t_wall *wall);
int is_walkable(t_game *game, float x, float y);
int clamp_point(int value, int min, int max);
float clamptexture(float value, float min, float max);
void set_wall(t_game *game, t_wall *wall);
void check_distance(t_rayhit *vhit, t_rayhit *hhit, t_wall *wall);

//utils folder
void close_and_free(t_game *game, int exit_code);
void free_game(t_game *game);
unsigned int get_texture(t_game *game, t_wall *wall, int y);
void my_mlx_pixel_put(t_image *img, int x, int y, int color);
void load_wall_image(t_game *game);

#endif