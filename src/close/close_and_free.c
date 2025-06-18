/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:24:56 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/18 20:05:05 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	close_and_free(t_game *game, int exit_code)
{
	if (game)
		free_game(game);
	exit (exit_code);
}

void	free_game(t_game *game)
{
	if (game && game->map)
		ft_free_array((void **)game->map);
	if (game && game->tmp_map)
		ft_free_array((void **)game->tmp_map);
	return ;
}