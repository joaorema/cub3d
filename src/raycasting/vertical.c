#include "../../inc/cub3d.h"

void v_top_down(t_game *game, t_rayhit *hit)
{
    (void)game;
    hit->dof = hit->max_dof;
    hit->rx = hit->px;
    hit->ry = hit->py;
}
void v_right(t_game *game, t_rayhit *hit, float ntan)
{
    (void)game;
    hit->rx = floor(hit->px / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
    hit->ry = (hit->px - hit->rx) * ntan + hit->py;
    hit->xo = TILE_SIZE;
    hit->yo = -hit->xo * ntan;
}

void v_left(t_game *game, t_rayhit *hit, float ntan)
{
    (void)game;
    hit->rx = floor(hit->px / TILE_SIZE) * TILE_SIZE - 0.0001;
    hit->ry = (hit->px - hit->rx) * ntan + hit->py;
    hit->xo = -TILE_SIZE;
    hit->yo = -hit->xo * ntan;
}

void update_vcheck(t_rayhit *hit)
{
    hit->rx += hit->xo;
    hit->ry += hit->yo;
    hit->dof++;
}
void final_vupdate(t_rayhit *hit)
{
    hit->x = hit->rx;
    hit->y = hit->ry;
    hit->distance = B_DISTANCE;
}
void vhit_wall(t_rayhit *hit, float ra)
{
    hit->x = hit->rx;
    hit->y = hit->ry;
    hit->distance = distance(hit->px, hit->py, hit->x, hit->y, ra);
}

void v_s_tile(t_rayhit *hit)
{
    hit->mx = (int)(hit->rx) / TILE_SIZE;
    hit->my = (int)(hit->ry) / TILE_SIZE;
}