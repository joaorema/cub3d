/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:30:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/24 22:24:09 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	char_is_valid(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '1' && c != '0'  && c != ' ')
		return (false);
	return(true);
}

void	set_pl_info(t_game *game, char c)
{
	game->player_direction = c;
	//game->player_x = x;
	//game->player_y = y;
}
