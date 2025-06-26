/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:16:00 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 19:39:16 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_raystruct(t_game *game, t_rayhit *hit)
{
	hit->player_pos = game->player.position;
	hit->depth_of_field = 0;
	hit->distance = 1000000.0f;
	if (game->map_width > game->map_height)
		hit->max_depth_of_field = game->map_width;
	else
		hit->max_depth_of_field = game->map_height;
}

void	init_rayhit(t_rayhit *hit, t_game *game, float angle)
{
	hit->player_pos = game->player.position;
	hit->ray_angle = angle;
	hit->depth_of_field = 0;
	hit->distance = 1000000.0f;
	hit->max_depth_of_field = 30;
}
