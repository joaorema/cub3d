/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:27 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/20 20:52:30 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include "../inc/mlx_linux/mlx.h"
#include "../inc/Mylib/libft.h"

int main(int ac, char *av[])
{
    t_game game;

    if (ac != 2)
    {
        ft_printf("Usage : %s <map_file> \n", av[0]);
        return (1); 
    }
    init(&game, av[1]);
    user_input(&game);
    mlx_loop_hook(game.mlx, game_loop,  &game);
    mlx_loop(game.mlx);
    return (0);
}
