/* ************************************************************************** */
/*																            */
/*                                                        :::      ::::::::   */
/*   02_vertical_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:32:43 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 14:35:30 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	v_top_down(t_game *game, t_rayhit *hit)
{
	(void)game;
	hit->depth_of_field = hit->max_depth_of_field;
	hit->next_ray_x = hit->player_pos.x;
	hit->next_ray_y = hit->player_pos.y;
}

void	v_right(t_game *game, t_rayhit *hit, float ntan)
{
	(void)game;
	hit->next_ray_x = floor(hit->player_pos.x / TILE_SIZE)
		* TILE_SIZE + TILE_SIZE;
	hit->next_ray_y = (hit->player_pos.x - hit->next_ray_x)
		* ntan + hit->player_pos.y;
	hit->x_offset = TILE_SIZE;
	hit->y_offset = -hit->x_offset * ntan;
}

void	v_left(t_game *game, t_rayhit *hit, float ntan)
{
	(void)game;
	hit->next_ray_x = floor(hit->player_pos.x / TILE_SIZE)
		* TILE_SIZE - 0.0001f;
	hit->next_ray_y = (hit->player_pos.x - hit->next_ray_x)
		* ntan + hit->player_pos.y;
	hit->x_offset = -TILE_SIZE;
	hit->y_offset = -hit->x_offset * ntan;
}

void	update_vcheck(t_rayhit *hit)
{
	hit->next_ray_x += hit->x_offset;
	hit->next_ray_y += hit->y_offset;
	hit->depth_of_field++;
}

void	final_vupdate(t_rayhit *hit)
{
	hit->hit_pos.x = hit->next_ray_x;
	hit->hit_pos.y = hit->next_ray_y;
	hit->distance = B_DISTANCE;
}
