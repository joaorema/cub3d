/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:35 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/18 19:51:52 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ch_and_load_map(t_game *game, char *file)
{
	if (ch_file(game, file))
		close_and_free(game, 2);
	set_height(game, file);
	game->map = malloc(sizeof(char *) * (game->map_height + 1));
	set_width_and_load(game, file);
	int i = -1;
	while (++i < game->map_height)
		ft_printf("%s\n", game->map[i]); //debug to delete

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
		len = get_line_len(line);
		if (len > game->map_width)
			game->map_width = len;
		add_line_to_map(game, line);
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