/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:30:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/25 23:39:59 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ch_dups(t_game *game, char *path, t_gnl gnl)
{
	if (path)
		print_err_and_exit(game, RED ERR DPINF RESET, 2 , &gnl);
}

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

