/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_load_and_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:35 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/26 00:50:49 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_and_parse_map(t_game *game, char *file)
{
	ch_file(game, file);
	set_height(game, file);
	game->map = calloc((game->map_height + 1), sizeof(char *));
	set_width_and_load(game, file);
	game->map[game->map_height] = NULL;
	set_map_info(game, file);
	print_map_info(game); //debug to delete
	parse_map_info(game);
}

void	ch_file(t_game *game, char *file)
{
	t_gnl	gnl;
	
	init_gnl(&gnl);
	if ((gnl.fd = safe_fd_open(file)) && (gnl.fd == -1))
		print_err_and_exit(game, NULL, 2, NULL);
	if (ft_strcmp(".cub", file + (ft_strlen(file) - 4)))
		print_err_and_exit(game, RED ERR EXT RESET, 2, &gnl);
	if (read(gnl.fd, &gnl.line, 1) <= 0) 
		print_err_and_exit(game, RED ERR EMPT RESET, 2, &gnl);
	close(gnl.fd);
}
