
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
	if (game->no_img.img)
    	mlx_destroy_image(game->mlx, game->no_img.img);
	if (game->so_img.img)
		mlx_destroy_image(game->mlx, game->so_img.img);
	if (game->we_img.img)
		mlx_destroy_image(game->mlx, game->we_img.img);
	if (game->ea_img.img)
		mlx_destroy_image(game->mlx, game->ea_img.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);	
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
