/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:35 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/17 18:35:32 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ch_and_load_map(t_game *game, char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (ch_file(file, fd))
		close_and_free(game, 2);
	set_width(game, fd);
	set_height(game, file);
	close(fd);
}

int	ch_file(char *file, int fd)
{
	char	*line;

	if (fd < 0)
	{
		ft_printf(RED"Error\n");
		ft_printf("Unable to open file\n"RESET);
		return (1);
	}
	if (ft_strcmp(".cub", file + (ft_strlen(file) - 4)))
	{
		ft_printf(RED"Error\n");
		ft_printf("File extension should be .cub\n"RESET);
		close (fd);
		return (1);
	}
	line = get_next_line(fd);
	if(!line)
	{
		ft_printf(RED"Error\n");
		ft_printf("Empty file or unable to read\n"RESET);
		close(fd);
		return (1);
	}
	line = safe_free(line);
	return (0);
}
