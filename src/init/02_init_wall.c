/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:16:24 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 21:17:01 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_wall(t_game *game, t_rayhits *hits, t_wall *wall,
			float angle)
{
	float	corrected_distance;
	float	offset;

	check_distance(&hits->v_hit, &hits->h_hit, wall);
	wall->screen_center_y = game->win_height / 2;
	corrected_distance = wall->distance * cos(angle - game->player_angle);
	wall->projected_height = (TILE_SIZE * 320) / corrected_distance;
	set_wall(wall);
	check_hit(wall, &angle, &offset);
	wall->texture_x = (int)(offset / TILE_SIZE * game->no_img.width);
	if ((wall->side == WEST) || (wall->side == SOUTH))
		wall->texture_x = game->no_img.width - wall->texture_x - 1;
	clamp_wall(game, wall);
}

void	clamp_wall(t_game *game, t_wall *wall)
{
	if (wall->texture_x < 0)
		wall->texture_x = 0;
	if (wall->texture_x >= game->no_img.width)
		wall->texture_x = game->no_img.width - 1;
}

void	set_wall(t_wall *wall)
{
	wall->top_pixel = wall->screen_center_y - wall->projected_height / 2;
	wall->bottom_pixel = wall->screen_center_y + wall->projected_height / 2;
}

void	check_hit(t_wall *wall, float *angle, float *offset)
{
	if (wall->hit_vertical)
	{
		if (cos(*angle) > 0)
			wall->side = EAST;
		else
			wall->side = WEST;
		*offset = fmod(wall->hit_point.y, TILE_SIZE);
	}
	else
	{
		if (sin(*angle) > 0)
			wall->side = SOUTH;
		else
			wall->side = NORTH;
		*offset = fmod(wall->hit_point.x, TILE_SIZE);
	}
}

void	check_distance(t_rayhit *vhit, t_rayhit *hhit, t_wall *wall)
{
	if (vhit->distance < hhit->distance)
	{
		wall->distance = vhit->distance;
		wall->hit_vertical = 1;
		wall->hit_point = vhit->hit_pos;
	}
	else
	{
		wall->distance = hhit->distance;
		wall->hit_vertical = 0;
		wall->hit_point = hhit->hit_pos;
	}
}
