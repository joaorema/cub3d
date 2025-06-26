/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:20:56 by isabel            #+#    #+#             */
/*   Updated: 2025/06/26 11:11:55 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	start_wind(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->map_width * 32,
			game->map_height * 32, "cub3d");
	mlx_put_image_to_window(game->mlx, game->win, game->txt->no, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->txt->ea, 64, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->txt->so, 64, 64);
	mlx_put_image_to_window(game->mlx, game->win, game->txt->we, 0, 64);
	mlx_hook(game->win, 17, 0L, close_window, game);
	mlx_loop(game->mlx);
}

int	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_printf(BLUE "The game has ended\n" RESET);
	close_and_free(game, 0);
	return (0);
}
