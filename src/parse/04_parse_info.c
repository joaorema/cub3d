/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:27:21 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/23 00:08:41 by isabel           ###   ########.fr       */
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
		print_err_and_exit(game, RED ERR MINF RESET, 2);
	if (!game->map_inf.c_rgb || !game->map_inf.f_rgb)
		print_err_and_exit(game, RED ERR COL RESET, 2);
	if (!game->map_height)
		print_err_and_exit(game, RED ERR MMAP RESET, 2);
}

void	ch_txt_paths(t_game *game)
{
	int	img_x;
	int	img_y;

	img_x = TILE_SIZE; //verificar com Joao
	img_y = TILE_SIZE; //verificar com Joao
	game->txt = calloc(1, sizeof(t_text));
	game->txt->NO = mlx_xpm_file_to_image(game->mlx, game->map_inf.no_pth, &img_x, &img_y);
	game->txt->SO = mlx_xpm_file_to_image(game->mlx, game->map_inf.so_pth, &img_x, &img_y);
	game->txt->WE = mlx_xpm_file_to_image(game->mlx, game->map_inf.we_pth, &img_x, &img_y);
	game->txt->EA = mlx_xpm_file_to_image(game->mlx, game->map_inf.ea_pth, &img_x, &img_y);	
	if (!game->txt->NO || !game->txt->SO || !game->txt->WE || !game->txt->EA)
		print_err_and_exit(game, RED ERR TXT RESET, 2);
}

