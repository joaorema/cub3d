#include "../../inc/cub3d.h"

void h_sides(t_game *game, t_rayhit *hit)
{
    (void)game;
    hit->dof = hit->max_dof;
    hit->rx = hit->px;
    hit->ry = hit->py;
}
void h_up(t_game *game, t_rayhit *hit, float atan)
{
    (void)game;
    hit->ry = floor(hit->py / TILE_SIZE) * TILE_SIZE - 0.0001;
    hit->rx = (hit->py - hit->ry) * atan + hit->px;
    hit->yo = -TILE_SIZE;
    hit->xo = -hit->yo * atan;
}

void h_down(t_game *game, t_rayhit *hit, float atan)
{
    (void)game;
    hit->ry = floor(hit->py / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    hit->rx = (hit->py - hit->ry) * atan + hit->px;
    hit->yo = TILE_SIZE;
    hit->xo = -hit->yo * atan;
}

void update_hcheck(t_rayhit *hit)
{
    hit->rx += hit->xo;
    hit->ry += hit->yo;
    hit->dof++;
}
void final_hupdate(t_rayhit *hit)
{
    hit->x = hit->rx;
    hit->y = hit->ry;
    hit->distance = B_DISTANCE;
}
void hhit_wall(t_rayhit *hit, float ra)
{
    hit->x = hit->rx;
    hit->y = hit->ry;
    hit->distance = distance(hit->px, hit->py, hit->x, hit->y, ra);
}

void h_s_tile(t_rayhit *hit)
{
    hit->mx = (int)(hit->rx) / TILE_SIZE;
    hit->my = (int)(hit->ry) / TILE_SIZE;
}