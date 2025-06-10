/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:02 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/10 16:27:09 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


t_game  start_game(t_game *game)
{
    game->map = NULL;
    game->temp_map = NULL;
    game->mlx = NULL;
    game->win = NULL;
    game->player = 0;
    game->player_x = 0;
    game->player_y = 0;
    game->map_width = 0;
    game->map_height = 0;
    return (*game);
}
