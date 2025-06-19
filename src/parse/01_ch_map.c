/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_ch_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:03:49 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/19 17:10:12 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void set_height(t_game *game, char *file)
{
	char *line;
	int	fd;

	if ((fd = safe_fd_open(file)) && (fd == -1))
		close_and_free(game, 2);
	while(1)
	{
	 	line = get_next_line(fd);
	 	if (!line)
	 		break;
		if (is_map(line))
		 	game->map_height++;
		line = safe_free(line);
	}
	close(fd);
	ft_printf("Map height: %d\n", game->map_height); //debug to delete
}

void set_width_and_load(t_game *game, char *file)
{
	int fd;
    char *line;
	int	len;

	if ((fd = safe_fd_open(file)) && (fd == -1))
		close_and_free(game, 2);
	while(1)
	{
		line = get_next_line(fd);
	 	if (!line)
	 		break;
		if (is_map(line))
		{
			len = get_line_len(line);
			if (len > game->map_width)
				game->map_width = len;
			add_line_to_map(game, line);	
		}
		line = safe_free(line);
	}
	close(fd);
	ft_printf("Map width: %d\n", game->map_width); //debug to delete
}

void add_line_to_map(t_game *game, char *line)
{
	int	len;
	static int	i;

	len = get_line_len(line);
	if (i < game->map_height)
	{
		game->map[i] = ft_strndup(line, (size_t)len);
		i++;
	}
}
