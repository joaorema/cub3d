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

void draw_rays(t_game *game)
{
    float ra;                      
    float aTan;
    float ry;
    float rx;
    float xo;
    float yo;   
    int dof;
    int mx;
    int my;
    
    
    ra = game->angle;
    dof = 0;
    aTan = -1/tan(ra);
    if(ra > PI)                                                 //Check if looking up
    {
        ry =(((int)game->player_y >> 6)<< 6)-0.0001;           //looking up
        rx = (game->player_y - ry)* aTan + game->player_x;
        yo = -64;
        xo = -yo * aTan;
    }
    else if(ra < PI)                                            //looking down
    {
        ry =(((int)game->player_y >> 6)<< 6) + 64;                
        rx = (game->player_y - ry) * aTan + game->player_x;
        yo = 64;
        xo = -yo * aTan;
    }
    else                                                       //looking left or right
    {
        rx = game->player_x;
        ry = game->player_y;
        dof = 8;
    }
    while(dof < 8)
    {
        mx = (int)(rx)>>6;
        my = (int)(ry)>>6;
        if (my >= 0 && my < game->map_height && mx >= 0 && mx < game->map_width && game->map[my][mx] == '1')
                break;
        rx += xo;
        ry += yo;
        dof++;
    }
    mlx_pixel_put(game->mlx, game->win, rx, ry, 0xFF0000);

}

