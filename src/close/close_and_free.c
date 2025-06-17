/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:24:56 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/17 17:44:43 by icunha-t         ###   ########.fr       */
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
	if (game->map)
		ft_free_array((void **)game->map);	
	return ;
}