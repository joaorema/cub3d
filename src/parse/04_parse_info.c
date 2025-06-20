/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:27:21 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/20 15:51:00 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_map_info(t_game *game)
{
	ch_missing_info(game);
}

void	ch_missing_info(t_game *game)
{
	if (!game->map_inf.no_pth || !game->map_inf.so_pth || !game->map_inf.we_pth
		|| !game->map_inf.ea_pth)
	{
		ft_printf(RED ERR MINF RESET);
		close_and_free(game, 2);
	}
	if (!game->map_inf.c_rgb || !game->map_inf.f_rgb)
	{
		ft_printf(RED ERR COL RESET);
		close_and_free(game, 2);
	}
	if (!game->map_height)
	{
		ft_printf(RED ERR MMAP RESET);
		close_and_free(game, 2);
	}
}
