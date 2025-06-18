/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:35 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/18 16:53:10 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ch_and_load_map(t_game *game, char *file)
{
	if (ch_file(game, file))
		close_and_free(game, 2);
	set_width(game, file);
	set_height(game, file);
}

int	ch_file(t_game *game, char *file)
{
	char	*line;
	int		fd;
	
	if ((fd = safe_fd_open(file)) && (fd == -1))
		close_and_free(game, 2);
	if (ft_strcmp(".cub", file + (ft_strlen(file) - 4)))
	{
		ft_printf(RED"Error\n");
		ft_printf("File extension should be .cub\n"RESET);
		close (fd);
		return (1);
	}
	if (read(fd, &line, 1) <= 0) 
	{
		ft_printf(RED"Error\n");
		ft_printf("Empty file or unable to read\n"RESET);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
