/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:44:46 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 14:44:51 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int ac, char *av[])
{
	t_game	game;

	if (ac != 2)
	{
		ft_printf("Usage : %s <map_file> \n", av[0]);
		return (1);
	}
	init(&game, av[1]);
	render_rays(&game);
	handle_keys(&game);
	loop(&game);
	return (0);
}
