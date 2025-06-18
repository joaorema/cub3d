/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:27 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/18 20:04:14 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int ac, char *av[])
{
	t_game game;

	if (ac != 2)
	{
		ft_printf(RED"Usage: %s <map_file> \n"RESET, av[0]);
		return (1);
	}
	init_game(&game);
	ch_and_load_map(&game, av[1]);
	//if (!parse_map(&game))
	//	return (1);
	close_and_free(&game, 0);
	return (0);
}
