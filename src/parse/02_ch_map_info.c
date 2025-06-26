/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_ch_map_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:03:39 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 18:38:03 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	set_map_info(t_game *game, char *file)
{
	t_gnl	gnl;

	init_gnl(&gnl);
	gnl.fd = safe_fd_open(file);
	if (gnl.fd == -1)
		print_err_and_exit(game, NULL, 2, NULL);
	while (1)
	{
		set_map_info_util(game, &gnl, 1);
		if (empty_line(gnl.l))
			continue ;
		else if (!gnl.l || is_map(gnl.l))
		{
			gnl.l = safe_free(gnl.l);
			break ;
		}
		if (!get_pth(game, gnl))
			set_map_info_util(game, &gnl, 2);
	}
	gnl_free_fd(gnl.fd);
	close(gnl.fd);
}

void	set_map_info_util(t_game *game, t_gnl *gnl, int n)
{
	if (n == 1)
	{
		gnl->l = safe_free(gnl->l);
		gnl->l = get_next_line(gnl->fd);
	}
	else
	{
		if (which_dir(gnl->l) == 5)
			add_f_and_c(game, *gnl);
		else
			print_err_and_exit(game, RED ERR WINF RESET, 2, &(*gnl));
	}
}

int	get_pth(t_game *game, t_gnl gnl)
{
	if (which_dir(gnl.l) == 1)
	{
		ch_dups(game, game->map_inf.no_pth, gnl);
		set_pth(game, gnl, &(game)->map_inf.no_pth);
		return (1);
	}
	else if (which_dir(gnl.l) == 2)
	{
		ch_dups(game, game->map_inf.so_pth, gnl);
		set_pth(game, gnl, &(game)->map_inf.so_pth);
		return (1);
	}
	else if (which_dir(gnl.l) == 3)
	{
		ch_dups(game, game->map_inf.ea_pth, gnl);
		set_pth(game, gnl, &(game)->map_inf.ea_pth);
		return (1);
	}
	else if (which_dir(gnl.l) == 4)
	{
		ch_dups(game, game->map_inf.we_pth, gnl);
		set_pth(game, gnl, &(game)->map_inf.we_pth);
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
	return (0);
}

void	set_pth(t_game *game, t_gnl gnl, char **set_str)
{
	int		i;
	char	path[2048];
	int		j;

	i = 0;
	while (ft_strchr(WS, gnl.l[i]))
		i++;
	i = i + 2;
	if (!ft_strchr(WS, gnl.l[i]))
		print_err_and_exit(game, RED ERR PTH RESET, 2, &gnl);
	while (ft_strchr(WS, gnl.l[i]))
		i++;
	j = 0;
	while (!ft_strchr(WS, gnl.l[i]))
		path[j++] = gnl.l[i++];
	path[j] = '\0';
	*set_str = ft_strdup(path);
	while (gnl.l[i])
	{
		if (!ft_strchr(WS, gnl.l[i]))
			print_err_and_exit(game, RED ERR PTH RESET, 2, &gnl);
		i++;
	}
}
