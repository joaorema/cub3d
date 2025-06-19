#include "../../inc/cub3d.h"


void draw_line(t_game *game)
{
    int i;
    float x;
    float y;

    i = 0;
    y = game->player_y;
    x = game->player_x;
    while (i < 20)
    {
        x += game->player_dx * 2;
        y += game->player_dy * 2;
        mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xFF0000);
        i++;
    }
}

void horizontal_check(t_game *game, t_rayhit *hit)                //horizontal check
{
    float ra;                      
    float aTan;
    float ry;
    float rx;
    float xo;
    float yo;
    float hx;
    float hy;
    float mdix;
    int dof;
    int mx;
    int my;
    int max_dof;

    mdix = 1000000;
    max_dof = (game->map_width > game->map_height) ? game->map_width : game->map_height;
    ra = game->angle;
    dof = 0;
    aTan = -1/tan(ra);
    hx = game->player_p_x;
    hy = game->player_p_y;
    if(ra > PI)                                                 //Check if looking up
    {
        ry =(((int)game->player_y /TILE_SIZE) * TILE_SIZE)-0.0001;           //gives y cordinate of top edge of tile player is in
        rx = (game->player_y - ry)* aTan + game->player_x;
        yo = -TILE_SIZE;
        xo = -yo * aTan;
    }
    else if(ra < PI)                                            //looking down
    {
        ry =(((int)game->player_y / TILE_SIZE )* TILE_SIZE) + TILE_SIZE;                
        rx = (game->player_y - ry) * aTan + game->player_x;
        yo = TILE_SIZE;
        xo = -yo * aTan;
    }
    else                                                       //looking left or right
    {
        rx = game->player_x;
        ry = game->player_y;
        dof = max_dof;
    }
    while(dof < max_dof)
    {
        mx = (int)(rx) / TILE_SIZE;
        my = (int)(ry) / TILE_SIZE;
        if (my >= 0 && my < game->map_height && mx >= 0 && mx < game->map_width && game->map[my][mx] == '1')
        {
            hx = rx;
            hy = ry;
            mdix = distance(game->player_p_x, game->player_p_y, hx, hy, ra);
            dof = 8;
        }
        rx += xo;
        ry += yo;
        dof++;
    }
    if (mx >= 0 && mx < game->map_width && my >= 0 && my < game->map_height)
    {
        // Only draw if hit point is inside the map
        hit->x = rx;
        hit->y = ry;
        hit->distance = mdix;
    }
    printf("Player: (%f, %f), Ray hit: (%f, %f)\n",
    (double)game->player_x, (double)game->player_y, rx, ry);

}

void vertical_check(t_game *game, t_rayhit *hit)                //vertical check 
{
    float ra;                      
    float nTan;
    float ry;
    float rx;
    float xo;
    float yo;
    float vx;
    float vy;
    float mver;  
    int dof;
    int mx;
    int my;
    int max_dof;

    mver = 1000000;
    max_dof = (game->map_width > game->map_height) ? game->map_width : game->map_height;
    ra = game->angle;
    dof = 0;
    nTan = -tan(ra);
    vx = game->player_p_x;
    vy = game->player_p_y;
    if(ra > P2 && ra < P3)                                                 //Check if looking left
    {
        rx =(((int)game->player_x /TILE_SIZE) * TILE_SIZE)-0.0001;           //gives y cordinate of top edge of tile player is in
        ry = (game->player_x - rx)* nTan + game->player_y;
        xo = -TILE_SIZE;
        yo = -xo * nTan;
    }
    else if(ra < P2 || ra > P3)                                            //check if looking right
    {
        rx =(((int)game->player_x / TILE_SIZE )* TILE_SIZE) + TILE_SIZE;                
        ry = (game->player_x - rx) * nTan + game->player_y;
        xo = TILE_SIZE;
        yo = -xo * nTan;
    }
    else                                                       //looking up or down
    {
        rx = game->player_x;
        ry = game->player_y;
        dof = max_dof;
    }
    while(dof < max_dof)
    {
        mx = (int)(rx) / TILE_SIZE;
        my = (int)(ry) / TILE_SIZE;
        if (my >= 0 && my < game->map_height && mx >= 0 && mx < game->map_width && game->map[my][mx] == '1')
        {
            vx = rx;
            vy = ry;
            mver = distance(game->player_p_x, game->player_p_y, vx, vy, ra);
            dof = 8;
        }
        rx += xo;
        ry += yo;
        dof++;
    }
    if (mx >= 0 && mx < game->map_width && my >= 0 && my < game->map_height)
    {
        // Only draw if hit point is inside the map
        hit->x = rx;
        hit->y = ry;
        hit->distance = mver;
    }
    printf("Player: (%f, %f), Ray hit: (%f, %f)\n",
    (double)game->player_x, (double)game->player_y, rx, ry);

}

float distance(float ax, float ay, float bx, float by, float ang)
{
    (void)ang;
    return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );                      //soma do quadrado dos catetos
}


void draw_ray_line(t_game *game, float rx, float ry)
{
    float x = game->player_x;
    float y = game->player_y;
    float dx = rx - x;
    float dy = ry - y;
    float steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);

    if (steps == 0)
        return;

    dx /= steps;
    dy /= steps;

    int i = 0;
    while (i < (int)steps)
    {
        mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xFF0000);
        x += dx;
        y += dy;
        i++;
    }
}

void draw_ray_line2(t_game *game, float rx, float ry)
{
    float x = game->player_x;
    float y = game->player_y;
    float dx = rx - x;
    float dy = ry - y;
    float steps = fabsf(dx) > fabsf(dy) ? fabsf(dx) : fabsf(dy);

    if (steps == 0)
        return;

    dx /= steps;
    dy /= steps;

    int i = 0;
    while (i < (int)steps)
    {
        mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, 0xFF0011);
        x += dx;
        y += dy;
        i++;
    }
}

void render_rays(t_game *game)
{
    t_rayhit h_hit;
    t_rayhit v_hit;



    // Get horizontal and vertical hits
    horizontal_check(game, &h_hit);
    vertical_check(game, &v_hit);

    // Compare distances and pick the closest
    if (h_hit.distance < v_hit.distance)
        draw_ray_line(game, h_hit.x, h_hit.y);
    else
        draw_ray_line2(game, v_hit.x, v_hit.y);
}