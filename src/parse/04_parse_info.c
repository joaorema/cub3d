/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:27:21 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 19:31:04 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_map_info(t_game *game)
{
	ch_missing_info(game);
	ch_txt_paths(game);
	ch_player_and_inv_chars(game);
	print_player_info(game); //debug to delete
	load_tmp_map(game);
	print_tmp_map(game, 1, NULL); //debug to delete
	ch_closed_walls(game, game->tmp_map, (game->map_height + 1),
		(game->map_width + 1));
}

void	ch_missing_info(t_game *game)
{
	if (!game->map_inf.no_pth || !game->map_inf.so_pth || !game->map_inf.we_pth
		|| !game->map_inf.ea_pth)
		print_err_and_exit(game, RED ERR MINF RESET, 2, NULL);
	if (!game->map_inf.c_rgb || !game->map_inf.f_rgb)
		print_err_and_exit(game, RED ERR COL RESET, 2, NULL);
	if (!game->map_height)
		print_err_and_exit(game, RED ERR MMAP RESET, 2, NULL);
}

void	ch_txt_paths(t_game *game)
{
	int	img_x;
	int	img_y;

	img_x = TILE_SIZE;
	img_y = TILE_SIZE;
	game->txt = calloc(1, sizeof(t_text));
	game->txt->no = mlx_xpm_file_to_image(game->mlx, game->map_inf.no_pth,
		&img_x, &img_y);
	game->txt->so = mlx_xpm_file_to_image(game->mlx, game->map_inf.so_pth,
		&img_x, &img_y);
	game->txt->we = mlx_xpm_file_to_image(game->mlx, game->map_inf.we_pth,
		&img_x, &img_y);
	game->txt->ea = mlx_xpm_file_to_image(game->mlx, game->map_inf.ea_pth,
		&img_x, &img_y);	
	if (!game->txt->no || !game->txt->so || !game->txt->we || !game->txt->ea)
		print_err_and_exit(game, RED ERR TXT RESET, 2, NULL);
}

void	ch_player_and_inv_chars(t_game *game)
{
	t_gnl 	gnl;
	int		i;
	int		j;
	
	init_gnl(&gnl);
	j = -1;
	while(game->map[++j])
	{
		gnl.line = ft_strdup(game->map[j]);
		i = -1;
		while(gnl.line[++i])
		{
			if (!char_is_valid(gnl.line[i]))
				print_err_and_exit(game, RED ERR INV RESET, 2, &gnl);
			if (play_char(gnl.line[i]))
			{
				if (game->player_direction != '\0')
					print_err_and_exit(game, RED ERR INV RESET, 2, &gnl);
				set_pl_info(game, gnl.line[i], i, j);
			}
		}
		gnl.line = safe_free(gnl.line);
	}
	if (game->player_direction == '\0')
		print_err_and_exit(game, RED ERR PL RESET, 2, &gnl);
}
