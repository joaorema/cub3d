/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:33 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/18 16:55:01 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void set_width(t_game *game, char *file)
{
	int fd;
    char *line;
	int	counter;

	if ((fd = safe_fd_open(file)) && (fd == -1))
		close_and_free(game, 2);
	while(1)
	{
		counter = 0;
		line = get_next_line(fd);
	 	if (!line)
	 		break;
	 	counter = (ft_strlen(line) - 1);
		if (counter > game->map_width)
			game->map_width = counter;
		line = safe_free(line);
	}
	close(fd);
	ft_printf("Map width: %d\n", game->map_width); //debug to delete
}

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
	 	game->map_height++;
		line = safe_free(line);
	}
	close(fd);
	ft_printf("Map height: %d\n", game->map_height); //debug to delete
}

int	safe_fd_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(RED"Error\n");
		ft_printf("Unable to open file\n"RESET);
		return (-1);
	}
	return (fd);
}
