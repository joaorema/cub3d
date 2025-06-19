#include "../../inc/cub3d.h"

void horizontal_check(t_game *game, t_rayhit *hit)
{
    float ra;
    float atan; 
    init_raystruct(game, hit);

    ra = hit->ra;
    atan = -1 / tan(ra);
    if (ra == 0 || ra == PI) // Looking exactly left/right — no horizontal hits
    {
        hit->dof = hit->max_dof;
        hit->rx = hit->px;
        hit->ry = hit->py;
    }
    else if (ra > PI) // Looking up
    {
        hit->ry = floor(hit->py / TILE_SIZE) * TILE_SIZE - 0.0001;
        hit->rx = (hit->py - hit->ry) * atan + hit->px;
        hit->yo = -TILE_SIZE;
        hit->xo = -hit->yo * atan;
    }
    else if (ra < PI) // Looking down
    {
        hit->ry = floor(hit->py / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        hit->rx = (hit->py - hit->ry) * atan + hit->px;
        hit->yo = TILE_SIZE;
        hit->xo = -hit->yo * atan;
    }

    while (hit->dof < hit->max_dof)
    {
        hit->mx = (int)(hit->rx) / TILE_SIZE;
        hit->my = (int)(hit->ry) / TILE_SIZE;

        if (hit->mx >= 0 && hit->mx < game->map_width &&
            hit->my >= 0 && hit->my < game->map_height &&
            game->map[hit->my][hit->mx] == '1')
        {
            hit->x = hit->rx;
            hit->y = hit->ry;
            hit->distance = distance(hit->px, hit->py, hit->x, hit->y, ra);
            return;
        }

        hit->rx += hit->xo;
        hit->ry += hit->yo;
        hit->dof++;
    }
    hit->x = hit->rx;
    hit->y = hit->ry;
    hit->distance = B_DISTANCE;
}

void vertical_check(t_game *game, t_rayhit *hit)
{
    float ra;
    float ntan;
    init_raystruct(game, hit);

    ra = hit->ra;
    ntan = -tan(ra);

    if (ra == P2 || ra == P3) // Looking exactly up/down — no vertical hits
    {
        hit->dof = hit->max_dof;
        hit->rx = hit->px;
        hit->ry = hit->py;
    }
    else if (ra < P2 || ra > P3) // Looking right
    {
        hit->rx = floor(hit->px / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
        hit->ry = (hit->px - hit->rx) * ntan + hit->py;
        hit->xo = TILE_SIZE;
        hit->yo = -hit->xo * ntan;
    }
    else if (ra > P2 && ra < P3) // Looking left
    {
        hit->rx = floor(hit->px / TILE_SIZE) * TILE_SIZE - 0.0001;
        hit->ry = (hit->px - hit->rx) * ntan + hit->py;
        hit->xo = -TILE_SIZE;
        hit->yo = -hit->xo * ntan;
    }

    while (hit->dof < hit->max_dof)
    {
        hit->mx = (int)(hit->rx) / TILE_SIZE;
        hit->my = (int)(hit->ry) / TILE_SIZE;

        if (hit->mx >= 0 && hit->mx < game->map_width &&
            hit->my >= 0 && hit->my < game->map_height &&
            game->map[hit->my][hit->mx] == '1')
        {
            hit->x = hit->rx;
            hit->y = hit->ry;
            hit->distance = distance(hit->px, hit->py, hit->x, hit->y, ra);
            return;
        }

        hit->rx += hit->xo;
        hit->ry += hit->yo;
        hit->dof++;
    }
    hit->x = hit->rx;
    hit->y = hit->ry;
    hit->distance = B_DISTANCE;
}

float distance(float ax, float ay, float bx, float by, float ang)
{
    (void)ang;
    return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );                      //soma do quadrado dos catetos
}
