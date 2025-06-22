/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:27 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/23 00:11:15 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int ac, char *av[])
{
	t_game game;

	init_game(&game);
	if (ac != 2)
		print_err_and_exit(&game, RED ERR USG RESET, 2);
	load_and_parse_map(&game, av[1]);
	//start_wind(&game);
	close_and_free(&game, 0);
	return (0);
}
