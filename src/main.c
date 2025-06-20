/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:27 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/20 17:02:45 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int ac, char *av[])
{
	t_game game;

	if (ac != 2)
	{
		ft_printf(RED ERR USG RESET);
		return (1);
	}
	init_game(&game);
	load_and_parse_map(&game, av[1]);
	//if (!parse_map(&game))
	//	return (1);
	close_and_free(&game, 0);
	return (0);
}
