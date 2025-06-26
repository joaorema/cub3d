/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:08:57 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 11:11:14 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_map_info(t_game *game)
{
	int	i;

	i = -1;
	ft_printf(GREEN"Map height:"RESET);
	ft_printf("%d\n", game->map_height);
	ft_printf(GREEN"Map width: "RESET);
	ft_printf("%d\n", game->map_width);
	if (game->map_inf.no_pth)
	{
		ft_printf(GREEN"north is: "RESET);
		ft_printf("%s\n", game->map_inf.no_pth);
	}
	if (game->map_inf.so_pth)
	{
		ft_printf(GREEN"south is: "RESET);
		ft_printf("%s\n", game->map_inf.so_pth);
	}
	if (game->map_inf.ea_pth)
	{
		ft_printf(GREEN"east is: "RESET);
		ft_printf("%s\n", game->map_inf.ea_pth);
	}
	if (game->map_inf.we_pth)
	{
		ft_printf(GREEN"west is: "RESET);
		ft_printf("%s\n", game->map_inf.we_pth);
	}
	if (game->map_inf.f_rgb)
	{
		ft_printf(GREEN"floor is: "RESET);
		ft_printf("%d, %d, %d\n", game->map_inf.f_rgb[0], game->map_inf.f_rgb[1], game->map_inf.f_rgb[2]);
	}
	if (game->map_inf.c_rgb)
	{
		ft_printf(GREEN"ceiling is: "RESET);
		ft_printf("%d, %d, %d\n", game->map_inf.c_rgb[0], game->map_inf.c_rgb[1], game->map_inf.c_rgb[2]);
	}
	ft_printf(GREEN"Map is:\n"RESET);
	while (++i < game->map_height)
		ft_printf("%s\n", game->map[i]);
}

void	print_player_info(t_game *game)
{
	if (game->player_dir != '\0')
	{
		ft_printf(GREEN"Player is:"RESET);
		ft_printf(" %c at line %d and col %d\n", game->player_dir, game->player_pos.y, game->player_pos.x);
	}
}

void	print_tmp_map(t_game *game, int n, t_point *pos)
{
	int	i;

	i = -1;
	if (n == 1)
	{
		ft_printf(GREEN"Tmp_map is:\n"RESET);
		while (++i < (game->map_height + 2))
			ft_printf("%s\n", game->tmp_map[i]);
	}
	if (n == 2)
	{
		ft_printf(GREEN"Tmp_map prepped for FF:\n"RESET);
		while (++i < (game->map_height + 2))
			ft_printf("%s\n", game->tmp_map[i]);
		if (pos)
			ft_printf("Starting position for FF is: line %d, col %d\n", (pos->y + 1), (pos->x + 1));
	}
	if (n == 3)
	{
		ft_printf(GREEN"Tmp_map after FF is:\n"RESET);
		while (++i < (game->map_height + 2))
			ft_printf("%s\n", game->tmp_map[i]);
	}
}
