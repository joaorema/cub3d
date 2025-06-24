/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parse_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:27:21 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/24 19:46:12 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parse_map_info(t_game *game)
{
	ch_missing_info(game);
	ch_txt_paths(game);
	ch_player_and_inv_chars(game);
	ch_closed_walls(game);
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

void	ch_player_and_inv_chars(t_game *game)
{
	char	*line;
	int		i;
	int		j;
	
	j = -1;
	while(game->map[++j])
	{
		line = ft_strdup(game->map[j]);
		i = -1;
		while(line[++i])
		{
			if (!char_is_valid(line[i]))
				print_err_and_exit(game, RED ERR INV RESET, 2);
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
			{
				if (game->player_dir != '\0')
					print_err_and_exit(game, RED ERR PL RESET, 2);
				set_pl_info(game, line[i], i, j);
			}
		}
		line = safe_free(line);
	}
	if (game->player_dir == '\0')
		print_err_and_exit(game, RED ERR PL RESET, 2);
}

void	ch_closed_walls(t_game *game)
{
	int		i;
	int		j;
	int		x;

	j = -1;
	i = -1;
	x = -1;
	game->tmp_map = malloc(sizeof(char *) * (game->map_height + 3));
	game->tmp_map[++x] = calloc(game->map_width + 3, sizeof(char));
	while (++i < (game->map_width + 1))
		game->tmp_map[x][i] = 'X';
	game->tmp_map[x][++i] = '\0';
	j = -1;
	while(game->map[++j])
	{
		i = 0;
		game->tmp_map[++x] = calloc(game->map_width + 3, sizeof(char));
		game->tmp_map[x][i] = 'X';
		while (i < (game->map_width + 1))
		{
			if ((i >= (int)ft_strlen(game->map[j]) )|| ft_strchr(WS, game->map[j][i]))
				game->tmp_map[x][i] = 'X';
			else				
				game->tmp_map[x][i] = game->map[j][i];
			i++;			
		}
		game->tmp_map[x][++i] = '\0';
	}
	i = -1;
	game->tmp_map[++x] = calloc(game->map_width + 3, sizeof(char));
	while (++i < (game->map_width + 1))
		game->tmp_map[x][i] = 'X';
	game->tmp_map[x][++i] = '\0';
	game->tmp_map[++x] = NULL;
}
