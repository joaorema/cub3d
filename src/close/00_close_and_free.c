/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/26 11:08:02 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_err_and_exit(t_game *game, char *err_msg, int exit, t_gnl *gnl)
{
	if (gnl && gnl->line)
		gnl->line = safe_free(gnl->line);
	if (gnl && gnl->fd != -1)
	{
		gnl_free_fd(gnl->fd);
		close(gnl->fd);
	}
	ft_putstr_fd(err_msg, 2);
	close_and_free(game, exit);
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
	if (game->txt && game->txt->no)
		mlx_destroy_image(game->mlx, game->txt->no);
	if (game->txt && game->txt->so)
		mlx_destroy_image(game->mlx, game->txt->so);
	if (game->txt && game->txt->we)
		mlx_destroy_image(game->mlx, game->txt->we);
	if (game->txt && game->txt->ea)
		mlx_destroy_image(game->mlx, game->txt->ea);
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

void	init_gnl(t_gnl *gnl)
{
	gnl->fd = -1;
	gnl->line = NULL;
}

void	init_ints(t_ints *ints)
{
	ints->i = -1;
	ints->j = -1;
	ints->x = 0;
	ints->z = 0;
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

int		close_x(void *param)
{
	t_game *game = (t_game *)param;
	if (game)
	{
		kill_visuals(game);
		free_game(game);
	}
	exit(0);
	return 0;
}