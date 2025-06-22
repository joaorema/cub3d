/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_close_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:24:56 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/22 23:58:20 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_err_and_exit(t_game *game, char *err_msg, int exit_code)
{
	ft_putstr_fd(err_msg, 2);
	close_and_free(game, exit_code);
}

void	close_and_free(t_game *game, int exit_code)
{
	if (game)
	{
		kill_visuals(game);
		free_game(game);
	}
	exit (exit_code);
}

void	free_game(t_game *game)
{
	if (game->map)
		ft_free_array((void **)game->map);
	if (game->tmp_map)
		ft_free_array((void **)game->tmp_map);
	if (game->map_inf.c_rgb)
		game->map_inf.c_rgb = safe_free(game->map_inf.c_rgb);
	if (game->map_inf.f_rgb)
		game->map_inf.f_rgb = safe_free(game->map_inf.f_rgb);
	if (game->map_inf.no_pth)
		game->map_inf.no_pth = safe_free(game->map_inf.no_pth);
	if (game->map_inf.so_pth)
		game->map_inf.so_pth = safe_free(game->map_inf.so_pth);
	if (game->map_inf.we_pth)
		game->map_inf.we_pth = safe_free(game->map_inf.we_pth);
	if (game->map_inf.ea_pth)
		game->map_inf.ea_pth = safe_free(game->map_inf.ea_pth);
	if (game->txt)
		game->txt = safe_free(game->txt);
	return ;
}

void	kill_visuals(t_game *game)
{
	if (!game)
		return ;
	if (game->txt && game->txt->NO)
		mlx_destroy_image(game->mlx, game->txt->NO);
	if (game->txt && game->txt->SO)
		mlx_destroy_image(game->mlx, game->txt->SO);
	if (game->txt && game->txt->WE)
		mlx_destroy_image(game->mlx, game->txt->WE);
	if (game->txt && game->txt->EA)
		mlx_destroy_image(game->mlx, game->txt->EA);
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
