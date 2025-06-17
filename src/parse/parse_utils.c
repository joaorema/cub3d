/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:33 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/17 18:41:23 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void set_width(t_game *game, int fd)
{
    char *line;

	line = get_next_line(fd);
	while(line != NULL)
	{
		line = get_next_line(fd);
		printf("line is %s\n", line);
		game->map_width++;
	}
	line = safe_free(line);
	ft_printf("Map width: %d\n", game->map_width); //debug to delete
}

void set_height(t_game *game, int fd)
{
    char *line;

	line = get_next_line(fd);
	while(1)
	{
	 	line = get_next_line(fd);
	 	printf("line is %s\n", line);
	 	if (!line)
	 		break;
	 	game->map_height++;
	}

	// game->map_height++;
	// line = get_next_line(fd);
	// while((line = get_next_line(fd)) != NULL)
	// {
	// 	line = get_next_line(fd);
	// 	game->map_height++;
	// }
	line = safe_free(line);
	ft_printf("Map height: %d\n", game->map_height); //debug to delete
}
    