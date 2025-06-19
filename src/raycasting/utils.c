#include "../../inc/cub3d.h"

void horizontal_check(t_game *game, t_rayhit *hit)                //horizontal check
{
   
    init_raystruct(game, hit);
    if(hit->ra < 0)
        hit->ra += 2 * PI;
    if(hit->ra > 2 * PI)
        hit->ra -= 2 * PI;

    hit->atan = -1/tan(hit->ra);
    if(hit->ra > PI)                                                 //Check if looking up
    {
        hit->ry =(((int)hit->py /TILE_SIZE) * TILE_SIZE)-0.0001;           //gives y cordinate of top edge of tile player is in
        hit->rx = (hit->py - hit->ry)* hit->atan + hit->px;
        hit->yo = -TILE_SIZE;
        hit->xo = -hit->yo * hit->atan;
    }
    else if(hit->ra < PI)                                            //looking down
    {
        hit->ry =(((int)hit->py / TILE_SIZE )* TILE_SIZE) + TILE_SIZE;                
        hit->rx = (hit->py - hit->ry) * hit->atan + hit->px;
        hit->yo = TILE_SIZE;
        hit->xo = -hit->yo * hit->atan;
    }
    else                                                       //looking left or right
    {
        hit->rx = hit->px;
        hit->ry = hit->py;
        hit->dof = hit->max_dof;
    }
    while(hit->dof < hit->max_dof)
    {
        hit->mx = (int)(hit->rx) / TILE_SIZE;
        hit->my = (int)(hit->ry) / TILE_SIZE;
        if(hit->my >= 0 && hit->my < game->map_height &&
           hit->mx >= 0 && hit->mx < game->map_width  &&
           game->map[hit->my][hit->mx] == '1')
        {
            hit->x = hit->rx;
            hit->y = hit->ry;
            hit->distance = distance(hit->px, hit->py, hit->rx, hit->ry, hit->ra);
            break;
        }
        else
        {
            hit->rx += hit->xo;
            hit->ry += hit->yo;
            hit->dof++;
        }
    }
    hit->x = hit->rx;
    hit->y = hit->ry;
    hit->distance = distance(hit->px, hit->py, hit->rx, hit->ry, hit->ra);
}

void vertical_check(t_game *game, t_rayhit *hit)                //vertical check 
{
    init_raystruct(game, hit);
    if(hit->ra < 0)
        hit->ra += 2 * PI;
    if(hit->ra > 2 * PI)
        hit->ra -= 2 * PI;
    hit->ntan = -tan(hit->ra);
    if(hit->ra > P2 && hit->ra < P3)                                                 //Check if looking left
    {
        hit->rx =(((int)hit->px /TILE_SIZE) * TILE_SIZE)-0.0001;           //gives y cordinate of top edge of tile player is in
        hit->ry = (hit->px - hit->rx)* hit->ntan + hit->py;
        hit->xo = -TILE_SIZE;
        hit->yo = -hit->xo * hit->ntan;
    }
    else if(hit->ra < P2 || hit->ra > P3)                                            //check if looking right
    {
        hit->rx =(((int)hit->px / TILE_SIZE )* TILE_SIZE) + TILE_SIZE;                
        hit->ry = (hit->px - hit->rx) * hit->ntan + hit->py;
        hit->xo = TILE_SIZE;
        hit->yo = -hit->xo * hit->ntan;
    }
    else                                                       //looking up or down
    {
        hit->rx = hit->px;
        hit->ry = hit->py;
        hit->dof = hit->max_dof;
    }
    while(hit->dof < hit->max_dof)
    {
        hit->mx = (int)(hit->rx) / TILE_SIZE;
        hit->my = (int)(hit->ry) / TILE_SIZE;
        if(hit->my >= 0 && hit->my < game->map_height &&
           hit->mx >= 0 && hit->mx < game->map_width  &&
           game->map[hit->my][hit->mx] == '1')
        {
            hit->x = hit->rx;
            hit->y = hit->ry;
            hit->distance = distance(hit->px, hit->py, hit->rx, hit->ry, hit->ra);
            break;
        }
        else
        {
            hit->rx += hit->xo;
            hit->ry += hit->yo;
            hit->dof++;
        }
    }
    hit->x = hit->rx;
    hit->y = hit->ry;
    hit->distance = distance(hit->px, hit->py, hit->rx, hit->ry, hit->ra);
}

float distance(float ax, float ay, float bx, float by, float ang)
{
    (void)ang;
    return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );                      //soma do quadrado dos catetos
}
