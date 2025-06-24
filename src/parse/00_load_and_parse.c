/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_load_and_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:35 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/25 00:07:09 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_and_parse_map(t_game *game, char *file)
{
	if (ch_file(game, file))
		close_and_free(game, 2);
	set_height(game, file);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	set_width_and_load(game, file);
	game->map[game->map_height] = NULL;
	set_map_info(game, file);
	parse_map_info(game);
	//print_map_info(game); //debug to delete
}

int	ch_file(t_game *game, char *file)
{
	char	*line;
	int		fd;
	
	if ((fd = safe_fd_open(file)) && (fd == -1))
		close_and_free(game, 2);
	if (ft_strcmp(".cub", file + (ft_strlen(file) - 4)))
	{
		ft_printf(RED ERR EXT RESET);
		close (fd);
		return (1);
	}
	if (read(fd, &line, 1) <= 0) 
	{
		ft_printf(RED ERR EMPT RESET);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
