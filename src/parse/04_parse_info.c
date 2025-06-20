/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:27:21 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/20 19:19:47 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_map_info(t_game *game)
{
	ch_missing_info(game);
	ch_txt_paths(game);
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
//HERE
void	ch_txt_paths(t_game *game)
{
	int	img_x;
	int	img_y;

	img_x = TILE_SIZE;
	img_y = TILE_SIZE;
	game->txt->NO = mlx_xpm_file_to_image(game->mlx, game->map_inf.no_pth, &img_x, &img_y);
	game->txt->SO = mlx_xpm_file_to_image(game->mlx, game->map_inf.so_pth, &img_x, &img_y);
	game->txt->WE = mlx_xpm_file_to_image(game->mlx, game->map_inf.we_pth, &img_x, &img_y);
	game->txt->EA = mlx_xpm_file_to_image(game->mlx, game->map_inf.ea_pth, &img_x, &img_y);	
	if (!game->txt->NO || !game->txt->SO || !game->txt->WE || !game->txt->EA)
	{
		ft_printf(RED ERR TXT RESET);
		close_and_free(game, 2);
	}
}