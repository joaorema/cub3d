/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_ch_map_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:03:39 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/24 17:56:39 by isabel           ###   ########.fr       */
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
			add_f_and_c(game, *line);
		else
		{
			*line = safe_free(*line);
			print_err_and_exit(game, RED ERR WINF RESET, 2);
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
	int		j;

	i = 0;
	while (ft_strchr(WS, line[i]))
		i++;
	i += i + 2;
	if (!ft_strchr(WS, line[i]))
		print_err_and_exit(game, RED ERR PTH RESET, 2);
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
		print_err_and_exit(game, RED ERR PTH RESET, 2);
		i++;
	}
}
