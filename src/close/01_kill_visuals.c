/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_kill_visuals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 09:28:28 by icunha-t          #+#    #+#             */
/*   Updated: 2025/07/03 09:31:00 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	kill_visuals(t_game *game)
{
	if (!game)
		return ;
	destroy_imgs(game);
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		game->mlx = safe_free(game->mlx);
		game->mlx = NULL;
	}
}

void	destroy_imgs(t_game *game)
{
	if (game->txt && game->txt->no)
		mlx_destroy_image(game->mlx, game->txt->no);
	if (game->txt && game->txt->so)
		mlx_destroy_image(game->mlx, game->txt->so);
	if (game->txt && game->txt->we)
		mlx_destroy_image(game->mlx, game->txt->we);
	if (game->txt && game->txt->ea)
		mlx_destroy_image(game->mlx, game->txt->ea);
	if (game->no_img.img)
		mlx_destroy_image(game->mlx, game->no_img.img);
	if (game->so_img.img)
		mlx_destroy_image(game->mlx, game->so_img.img);
	if (game->ea_img.img)
		mlx_destroy_image(game->mlx, game->ea_img.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->we_img.img)
		mlx_destroy_image(game->mlx, game->we_img.img);
}
