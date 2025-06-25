/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:30:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/25 18:49:29 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	char_is_valid(char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '1' && c != '0'
		&& c != ' ')
		return (false);
	return(true);
}

bool	play_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return(false);
}

void	set_pl_info(t_game *game, char c, int x, int y)
{
	game->player_dir = c;
	game->player_pos.x = x + 1;
	game->player_pos.y = y + 1;
}

