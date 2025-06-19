/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_ch_map_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:03:39 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/19 19:56:47 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"



void	set_map_info(t_game *game, char *file)
{
	char	*line;
	int		fd;

	if ((fd = safe_fd_open(file)) && (fd == -1))
		close_and_free(game, 2);
	line = NULL;
	while(1)
	{
		if (line)
			line = safe_free(line);
		line = get_next_line(fd);
		if (empty_line(line))
			continue ;
	 	else if (!line || is_map(line))
		{
			if (line)
				line = safe_free(line);
			break;	
		}
		if (!get_pth(game, line))
		{
			if (which_dir(line) == 5)
				add_fl_and_c(game, line);
			else
			{
				line = safe_free(line);
				ft_printf(RED ERR INF RESET);
				close_and_free(game, 2);
			}	
		}
		line = safe_free(line);
	}
	close(fd);
}

int get_pth(t_game *game, char *line)
{
	if (which_dir(line) == 1)
	{
		set_pth(line, &(game)->map_inf.no_pth);
		return (1);
	}
	else if (which_dir(line) == 2)
	{
		set_pth(line, &(game)->map_inf.so_pth);
		return (1);
	}
	else if (which_dir(line) == 3)
	{
		set_pth(line, &(game)->map_inf.ea_pth);
		return (1);
	}	
	else if (which_dir(line) == 4)
	{	
		set_pth(line, &(game)->map_inf.we_pth);
		return (1);
	}
	return (0);
}

int	which_dir(char *line)
{
	int		i;
	char	c;
	char	n;

	i = 0;
	while (ft_strchr(WS, line[i]))
		i++;
	c = line[i];
	n = line [i + 1];
	if (c == 'N' && n == 'O')
		return (1);
	else if (c == 'S' && n == 'O')
		return (2);
	else if (c == 'E' && n == 'A')
		return (3);
	else if (c == 'W' && n == 'E')
		return (4);
	else if (c == 'F' || c == 'C')
		return (5);
	return(0);
}

void set_pth(char *line, char **set_str)
{
	int		i;
	int		start;
	int		len;
	
	i = 0;
	len = 0;
	while (line[i] != '.')
		i++;
	start = i;
	while(line[i] && !ft_strchr(WS, line[i]))
	{
		len++;
		i++;
	}
	*set_str = ft_substr((const char *)line, (unsigned int)start, (size_t)len);
}
