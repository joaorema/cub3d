/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_horizontal_variables_utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:01:04 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 21:05:45 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	hhit_wall(t_rayhit *hit)
{
	hit->hit_pos.x = hit->next_ray_x;
	hit->hit_pos.y = hit->next_ray_y;
	hit->distance = distance(
			hit->player_pos.x,
			hit->player_pos.y,
			hit->hit_pos.x,
			hit->hit_pos.y);
}

void	h_s_tile(t_rayhit *hit)
{
	hit->map_x = (int)(hit->next_ray_x) / TILE_SIZE;
	hit->map_y = (int)(hit->next_ray_y) / TILE_SIZE;
}
