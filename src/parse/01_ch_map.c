/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_ch_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:03:49 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 00:51:18 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void set_height(t_game *game, char *file)
{
	t_gnl	gnl;
	
	init_gnl(&gnl);
	if ((gnl.fd = safe_fd_open(file)) && (gnl.fd == -1))
		print_err_and_exit(game, NULL, 2, NULL);
	while(1)
	{
	 	gnl.line = get_next_line(gnl.fd);
	 	if (!gnl.line)
	 		break;
		if (is_map(gnl.line))
		 	game->map_height++;
		gnl.line = safe_free(gnl.line);
	}
	close(gnl.fd);
}

void set_width_and_load(t_game *game, char *file)
{
	t_gnl 	gnl;
	bool	map_limit;

	init_gnl(&gnl);
	map_limit = false;
	if ((gnl.fd = safe_fd_open(file)) && (gnl.fd == -1))
		print_err_and_exit(game, NULL, 2, NULL);
	while(1)
	{
		gnl.line = get_next_line(gnl.fd);			
	 	if (!gnl.line)
	 		break;
		if (is_map(gnl.line))
			set_width_and_load_util(game, &map_limit, gnl.line);		
		else if (map_limit)
		{
			game->map[game->map_height] = NULL;
			print_err_and_exit(game, RED ERR INFAFTMAP RESET, 2, &gnl);	
		}
		gnl.line = safe_free(gnl.line);
	}
	close(gnl.fd);
}

void	set_width_and_load_util(t_game *game, bool *map_limit, char *line)
{
	int	len;

	*map_limit = true;
	len = get_line_len(line);
	if (len > game->map_width)
		game->map_width = len;
	if (!only_ws(line))
		add_line_to_map(game, line);	
}

bool	only_ws(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!ft_strchr(WS, line[i]))
			return (false);	
	}
	return (true);		
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
