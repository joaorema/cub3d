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
    int r;
    int mx;
    int my;
    int mp;

    r = 0;
    ra = game->angle;
    while(r < 1)
    {
        dof = 0;
        aTan = -1/tan(ra);
        if(ra > PI)                                                 //Check if looking up or down
        {
            ry =(((int)game->player_y >> 6)<< 6)-0.0001;           //looking up
            rx = (game->player_y - ry)* aTan + game->player_dx;
            yo = -64;
            xo = -yo * aTan;
        }
        if(ra < PI)
        {
            ry =(((int)game->player_y >> 6)<< 6)+64;                //looking down
            rx = (game->player_y - ry)* aTan + game->player_dx;
            yo = 64;
            xo = -yo * aTan;
        }
        if(ra == 0 || ra == PI)
        {
            rx = game->player_x;
            ry = game->player_y;
            dof = 8;
        }
        while(dof < 8)
        {
            mx = (int)(rx)>>6;
            my = (int)(ry)>>6;
            mp = my * game->map_width + mx;
            if (my >= 0 && my < game->map_height && mx >= 0 && mx < game->map_width && game->map[my][mx] == '1')
                dof = 8;                                        //break the loop
            else
            {
                rx += xo;
                ry += yo;
                dof += 1;
            }
        }
        mlx_pixel_put(game->mlx, game->win, rx, ry, 0xFF0000);
    }

}