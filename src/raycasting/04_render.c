#include "../../inc/cub3d.h"

void render_rays(t_game *game)                                              //main raycast that draws everything
{
    int i;
    float ray_angle;

    i = 0;
    ray_angle = game->player_angle - (FOV / 2);
    while (i < NUM_RAYS)                                                    //Num rays = 60
    {
        render_wall(game, ray_angle, i);
        ray_angle += ANGLE_STEP;

        if (ray_angle < 0)
            ray_angle += 2 * PI;
        if (ray_angle > 2 * PI)
            ray_angle -= 2 * PI;
        i++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);     //puts wall image
}

void render_wall(t_game *game, float angle, int ray_index)                  //
{
    t_rayhit v_hit;
    t_rayhit h_hit;
    t_wall wall;
    t_rayhits new_hit;

    init_rayhit(&v_hit, game, angle);                                       //starts vertical hit struct
    init_rayhit(&h_hit, game, angle);                                       //starts horizontal hit struct
    horizontal_check(game, &h_hit);                                         //checks angle and updates h_struct to have current horizontal ray    
    vertical_check(game, &v_hit);                                           //checks angle and updates v_struct to have current vertical ray
    wall.screen_x = (ray_index);   
    wall.slice_width = 1;
    new_hit.h_hit = h_hit;
    new_hit.v_hit = v_hit;
    init_wall(game, &new_hit, &wall, angle);                          //starts wall struct using v_hit and h_hit
    draw_topbottom(game, &wall);                                            //draw sky and floor
    draw_wall_slice(game, &wall);                                           //draw the wall
}

void draw_topbottom(t_game *game, t_wall *wall)
{
    int x;
    int w;
    int sky_height;
    int floor_height;

    x = wall->screen_x;
    w = 0;
    while (w < wall->slice_width)
    {
        sky_height = (int)wall->top_pixel;
        floor_height = game->win_height - (int)wall->bottom_pixel;
        if (sky_height > 0)                                                            
            draw(&game->img, (t_point){x + w, 0}, (t_point){1, sky_height}, game->sky_color);
        if (floor_height > 0)                                                          
            draw(&game->img, (t_point){x + w, (int)wall->bottom_pixel}, (t_point){1, floor_height}, game->floor_color);
        w++;
    }
}

void draw_wall_slice(t_game *game, t_wall *wall)
{
    t_point pos;                    
    int y_start;
    int y_end;
    unsigned int color;
    int y;

    pos.x = wall->screen_x;
    pos.y = 0;
    y_start = (int)wall->top_pixel;
    y_end = (int)wall->bottom_pixel;
    if (y_start >= y_end)
        return;
    while (pos.y < wall->slice_width)
    {
        y = y_start;
        while (y < y_end)
        {
            color = get_texture(game, wall, y);
            my_mlx_pixel_put(&game->img, pos.x + pos.y, y, color);
            y++;
        }
        pos.y++;
    }
}

