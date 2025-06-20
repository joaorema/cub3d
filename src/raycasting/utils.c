#include "../../inc/cub3d.h"

void horizontal_check(t_game *game, t_rayhit *hit)
{
    float ra;
    float atan; 
    
    init_raystruct(game, hit);
    ra = hit->ra;
    atan = -1 / tan(ra);
    if (ra == 0 || ra == PI)                // Looking exactly left/right — no horizontal hits
        h_sides(game, hit);
    else if (ra > PI)                       // Looking up
        h_up(game, hit, atan);
    else if (ra < PI)                       // Looking down
        h_down(game, hit, atan);
    while (hit->dof < hit->max_dof)
    {
        h_s_tile(hit);
        if (hit->mx >= 0 && hit->mx < game->map_width &&
            hit->my >= 0 && hit->my < game->map_height &&
            game->map[hit->my][hit->mx] == '1')
        {
            hhit_wall(hit, ra);
            return;
        }
        update_hcheck(hit);
    }
    final_hupdate(hit);
}

void vertical_check(t_game *game, t_rayhit *hit)
{
    float ra;
    float ntan;
    
    init_raystruct(game, hit);
    ra = hit->ra;
    ntan = -tan(ra);
    if (ra == P2 || ra == P3) // Looking exactly up/down — no vertical hits
        v_top_down(game, hit);
    else if (ra < P2 || ra > P3) // Looking right
        v_right(game, hit, ntan);
    else if (ra > P2 && ra < P3) // Looking left
        v_left(game, hit, ntan);
    while (hit->dof < hit->max_dof)
    {
        v_s_tile(hit);
        if (hit->mx >= 0 && hit->mx < game->map_width &&
            hit->my >= 0 && hit->my < game->map_height &&
            game->map[hit->my][hit->mx] == '1')
        {
            vhit_wall(hit, ra);
            return;
        }
        update_vcheck(hit);
    }
    final_vupdate(hit);
}

float distance(float ax, float ay, float bx, float by, float ang)
{
    (void)ang;
    return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );                      //soma do quadrado dos catetos
}



