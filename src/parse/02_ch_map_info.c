/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_ch_map_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:03:39 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/20 18:55:47 by icunha-t         ###   ########.fr       */
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
		set_map_info_util(game, &line, fd, 1);		
		if (empty_line(line))
			continue ;
	 	else if (!line || is_map(line))
		{
			line = safe_free(line);
			break;
		}
		if (!get_pth(game, line))
			set_map_info_util(game, &line, fd, 2);
	}
	gnl_free_fd(fd);
	close(fd);
}

void	set_map_info_util(t_game *game, char **line, int fd, int n)
{	
	if (n == 1)
	{
		*line = safe_free(*line);
		*line = get_next_line(fd);	
	}
	else
	{
		if (which_dir(*line) == 5)
			add_fl_and_c(game, *line);
		else
		{
			*line = safe_free(*line);
			ft_printf(RED ERR MINF RESET);
			close_and_free(game, 2);
		}	
	}
}

int get_pth(t_game *game, char *line)
{
	if (which_dir(line) == 1)
	{
		set_pth(game, line, &(game)->map_inf.no_pth);
		return (1);
	}
	else if (which_dir(line) == 2)
	{
		set_pth(game, line, &(game)->map_inf.so_pth);
		return (1);
	}
	else if (which_dir(line) == 3)
	{
		set_pth(game, line, &(game)->map_inf.ea_pth);
		return (1);
	}	
	else if (which_dir(line) == 4)
	{	
		set_pth(game, line, &(game)->map_inf.we_pth);
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

void set_pth(t_game *game, char *line, char **set_str)
{
	int		i;
	char	path[2048];
	char	id[3];
	int		j;

	i = 0;
	while (ft_strchr(WS, line[i]))
		i++;
	id[0] = line[i++];
	id[1] = line[i++];
	id[2] = '\0';
	while (ft_strchr(WS, line[i]))
		i++;
	j = 0;
	while(!ft_strchr(WS, line[i]))
		path[j++] = line[i++];
	path[j] = '\0';
	*set_str = ft_strdup(path);
	while (line[i])
	{
		if (!ft_strchr(WS, line[i]))
		{
			ft_printf(RED ERR PTH RESET);
	 		close_and_free(game, 2);
		}
		i++;
	}
}

// void set_pth(t_game *game, char *line, char **set_str)
// {
// 	int		i;
// 	int		start;
// 	int		len;
	
// 	i = 0;
// 	len = 0;
// 	while (line[i] != '.')
// 	{
// 		// if (!ft_strchr(WS, line[i]))
// 		// {
// 		// 	ft_printf(RED ERR PTH RESET);
// 		// 	close_and_free(game, 2);
// 		// }
// 		(void)game;
// 		i++;	
// 	}
// 	start = i;
// 	while(line[i] && !ft_strchr(WS, line[i]))
// 	{
// 		len++;
// 		i++;
// 	}
// 	*set_str = ft_substr((const char *)line, (unsigned int)start, (size_t)len);
// }
