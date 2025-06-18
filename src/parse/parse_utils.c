/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:33 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/18 19:28:39 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_line_len(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len > 0 && line[len - 1] == '\r')
		len--;
	return (len);
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
