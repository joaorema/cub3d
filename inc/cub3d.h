/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/25 23:40:18 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "Mylib/libft.h"
#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

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
# define RESET      "\033[0m"
# define RED        "\033[1;31m"
# define GREEN      "\033[1;32m"
# define BLUE       "\033[1;36m"
# define SKY        0xFFADD8E6
# define FLOOR      0x00333333

//keycodes
# define KEY_ESC    65307
# define KEY_W      119
# define KEY_A      97
# define KEY_S      115
# define KEY_D      100
# define KEY_LEFT   65361
# define KEY_RIGHT  65363
# define MOVE_SPEED 05.0f


//constants
# define PI         3.1415926535
# define P2         PI/2
# define P3         3*PI/2
# define NORTH      0
# define SOUTH      1
# define WEST       2
# define EAST       3
# define WS         " \t\n\r\v\f"
# define CH_MAP     "01NSEW"
# define N_CH_MAP   "01 \t\n\r\v\f"
# define NB         "0123456789"

//game settings
# define WIDTH      800
# define HEIGHT     800
# define NUM_RAYS   WIDTH
# define FOV        (PI / 3)            //60º angle
# define ANGLE_STEP (FOV / NUM_RAYS)    //0.00131 radians
# define B_DISTANCE 100000
# define TILE_SIZE  64 
# define P_RADIUS   (TILE_SIZE * 0.35f)            
# define ROT_SPEED  0.03f


//structs
typedef struct s_keys
{
    int         w;
    int         s;
    int         a;
    int         d;
    int         left;
    int         right;
}   t_keys;

typedef struct s_map_inf
{
	char	    *no_pth;
	char	    *so_pth;
	char	    *ea_pth;
	char	    *we_pth;
	int		    *f_rgb;
	int         *c_rgb;
} t_map_inf;

typedef struct s_text
{
	void        *NO;
	void        *SO;
	void        *WE;
	void        *EA;
}	t_text;

typedef struct s_point
{
    float       x;
    float       y;
    
} t_point;

typedef struct s_image
{
    void        *img;
    char        *addr;
    int         width;
    int         height;
    int         bits_per_pixel;
    int         line_len;
    int         endian;
    t_point     pos;
    
}   t_image;

typedef struct s_wall
{
    int         texture_x;                                  // X coordinate on wall texture to sample
    int         screen_x;                                   // X coordinate on screen to draw slice
    int         slice_width;                                // Width of the vertical slice of the wall
    int         hit_vertical;                               // Boolean: did the ray hit a vertical wall?
    float       ray_angle;
    float       distance;                                 // Distance from player to wall hit
    float       projected_height;                         // Height of wall slice to draw on screen
    float       top_pixel;                                // Screen y-coordinate for top of wall slice
    float       bottom_pixel;                             // Screen y-coordinate for bottom of wall slice
    float       screen_center_y;                          // Vertical center of screen (win_height/2)
    int         side;
    t_point     hit_point;                              // Coordinates where ray hit the wall

}   t_wall;

typedef struct s_rayhit
{
    int         depth_of_field;                             // Current depth of field (number of checks)
    int         map_x;                                      // Map grid X coordinate of hit
    int         map_y;                                      // Map grid Y coordinate of hit
    float       distance;                                 // Distance from player to hit point
    float       ray_angle;                                // Angle of the current ray
    float       atan_angle;                               // Auxiliary values for raycasting calculations
    float       ntan_angle;
    float       next_ray_y;                               // Next intersection Y coordinate for checking grid
    float       next_ray_x;                               // Next intersection X coordinate for checking grid
    float       x_offset;                                 // Step increment X for ray movement
    float       y_offset;                                 // Step increment Y for ray movement
    float       max_horizontal;                           // Max horizontal distance limit for ray
    float       max_vertical;                             // Max vertical distance limit for ray
    float       max_depth_of_field;                       // Max steps before raycasting stops
    t_point     hit_pos;                                // Coordinates where the ray hits something
    t_point     player_pos;                             // Player's current position
    
} t_rayhit;

typedef struct s_player
{
    int         tile_x;               // Player tile/grid X coordinate
    int         tile_y;               // Player tile/grid Y coordinate
    t_point     delta;            // Movement delta per frame (dx, dy)
    t_point     position;         // Player world coordinates (x, y)
    t_point     pixel_offset;     // Pixel offset within current tile

}   t_player;


typedef struct s_game
{
    void        *mlx;
    void        *win;
    int         map_width;            // Width of the map in tiles
    int         map_height;           // Height of the map in tiles
    int         win_width;            // Window width in pixels
    int         win_height;           // Window height in pixels
    t_keys      keys;
    char        **map;
    char        **tmp_map;
    char        player_direction;
    float       player_angle;       // Player looking angle in radians
    int         floor_color;
    int         sky_color;
    t_map_inf   map_inf;
    t_text      *txt;
    t_player    player;
    t_image     img;
    t_image     no_img;
    t_image     so_img;
    t_image     we_img;
    t_image     ea_img;
    
} t_game;

//close folder
void	print_err_and_exit(t_game *game, char *err_msg, int exit_code);
void	close_and_free(t_game *game, int exit_code);
void	free_game(t_game *game);
void	kill_visuals(t_game *game);

//init folder
void    init_game_struct(t_game *game);
void    init_map(t_game *game);
void    init_player(t_game *game);
void    init(t_game *game, char *file);
void    init_raystruct(t_game *game, t_rayhit *hit);
void    init_rayhit(t_rayhit *hit, t_game *game, float angle);
void    init_wall(t_game *game, t_rayhit *vhit, t_rayhit *hhit, t_wall *wall, float angle);
void    set_wall(t_wall *wall);
void    check_distance(t_rayhit *vhit, t_rayhit *hhit, t_wall *wall);
void    find_player(t_game *game);             //
void    render_map(t_game *game);          
int     game_loop(t_game *game);
void    init_images(t_game *game);
void    set_player_angle(t_game *game, char dir);
void    init_keys(t_game *game);
void    check_hit(t_wall *wall, float *angle, float *offset);
void    handle_keys(t_game *game);
void    loop(t_game *game);
int     move_player(t_game *game);
void clamp_wall(t_game *game, t_wall *wall);


//parse folder
void    load_and_parse_map(t_game *game, char *file);
int	    ch_file(t_game *game, char *file);
void    set_height(t_game *game, char *file);
void    set_width_and_load(t_game *game, char *file);
bool	only_ws(char *line);
void    add_line_to_map(t_game *game, char *line);
void	set_map_info(t_game *game, char *file);
void	set_map_info_util(t_game *game, char **line, int fd, int n);
int     get_pth(t_game *game, char *line);
int	    which_dir(char *line);
void    set_pth(t_game *game, char *line, char **set_str);
void    add_f_and_c(t_game *game, char *line);
int	    get_rgb_val(t_game *game, char *line, int *start);
void	ch_mid_val(t_game *game, char c, bool *ch, int n);
void	set_rgb(t_game *game, char *line, int f_val, int s_val, int t_val);
void	parse_map_info(t_game *game);
void	ch_missing_info(t_game *game);
void	ch_txt_paths(t_game *game);
void	ch_player_and_inv_chars(t_game *game);
void	ch_closed_walls(t_game *game);
int	    get_line_len(char *line);
int	    safe_fd_open(char *file);
int	    is_map(char *line);
int	    empty_line(char *line);
bool	char_is_valid(char c);
void	set_pl_info(t_game *game, char c);
int     create_trgb(int r, int g, int b);

//player folder
int     player_move(t_game *game, float m_x, float m_y);
int     is_walkable(t_game *game, float x, float y);
int	    handle_keyboard(int keycode, t_game *game);
int     player_direction(int keycode, t_game *game);
void    user_input(t_game *game);
int     key_released(int keycode, t_game *game);
void    rotate_player(t_game *game, float rotation);
//raycasting init
void    horizontal_check(t_game *game, t_rayhit *hit);
void    h_sides(t_game *game, t_rayhit *hit);
void    h_up(t_game *game, t_rayhit *hit, float atan);
void    h_down(t_game *game, t_rayhit *hit, float atan);
void    update_hcheck(t_rayhit *hit);
void    final_hupdate(t_rayhit *hit);
void    hhit_wall(t_rayhit *hit, float ra);
void    h_s_tile(t_rayhit *hit);
void    vertical_check(t_game *game, t_rayhit *hit);
void    v_top_down(t_game *game, t_rayhit *hit);
void    v_right(t_game *game, t_rayhit *hit, float ntan);
void    v_left(t_game *game, t_rayhit *hit, float ntan);
void    update_vcheck(t_rayhit *hit);
void    final_vupdate(t_rayhit *hit);
void    vhit_wall(t_rayhit *hit, float ra);
void    v_s_tile(t_rayhit *hit);
float   distance(float ax, float ay, float bx, float by, float ang);              //hipotenusa

//raycasting folder
void    render_rays(t_game *game);
void    render_wall(t_game *game, float angle, int col);
void    draw_topbottom(t_game *game, t_wall *wall);
void    draw_wall_slice(t_game *game, t_wall *wall);
void	draw(t_image *image, t_point pos, t_point size, int color);
void    my_mlx_pixel_put(t_image *img, int x, int y, int color);
void    load_wall_images(t_game *game);
int     clamp_point(int value, int min, int max);
float   clamptexture(float value, float min, float max);
t_image *set_side(t_game *game, t_wall *wall);
unsigned int get_texture(t_game *game, t_wall *wall, int y);

#endif