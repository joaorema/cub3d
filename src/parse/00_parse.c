/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:35 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/19 18:45:03 by icunha-t         ###   ########.fr       */
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
	game->map[game->map_height] = NULL;
	int i = -1; //debug to delete
	set_map_info(game, file);
	if (game->map_inf.no_pth)//debug to delete
		ft_printf("north is: %s\n", game->map_inf.no_pth);
	if (game->map_inf.so_pth)
		ft_printf("south is: %s\n", game->map_inf.so_pth);
	if (game->map_inf.ea_pth)
		ft_printf("east is: %s\n", game->map_inf.ea_pth);
	if (game->map_inf.we_pth)
		ft_printf("west is: %s\n", game->map_inf.we_pth);
	if (game->map_inf.f_rgb)
		ft_printf("floor is: %d, %d, %d\n", game->map_inf.f_rgb[0], game->map_inf.f_rgb[1], game->map_inf.f_rgb[2]);
	if (game->map_inf.c_rgb)
		ft_printf("ceiling is: %d, %d, %d\n", game->map_inf.c_rgb[0], game->map_inf.c_rgb[1], game->map_inf.c_rgb[2]); //debug to delete
	while (++i < game->map_height)
		ft_printf("%s\n", game->map[i]);//debug to delete
}

int	ch_file(t_game *game, char *file)
{
	char	*line;
	int		fd;
	
	if ((fd = safe_fd_open(file)) && (fd == -1))
		close_and_free(game, 2);
	if (ft_strcmp(".cub", file + (ft_strlen(file) - 4)))
	{
		ft_printf(RED ERR EXT RESET);
		close (fd);
		return (1);
	}
	if (read(fd, &line, 1) <= 0) 
	{
		ft_printf(RED ERR EMPT RESET);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
