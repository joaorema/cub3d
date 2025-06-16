/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:27 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/10 16:38:46 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"
#include "inc/mlx_linux/mlx.h"
#include "inc/Mylib/libft.h"

int main(int ac, char *av[])
{
    t_game game;
    
    if (ac != 2)
    {
        ft_printf("Usage : %s <map_file> \n", av[0]);
        return (1); 
    }
    start_game(&game);
    count_height(&game, av[1]);
    count_width(&game, av[1]);
    game.win = mlx_new_window(game.mlx, game.map_width * TILE_SIZE, game.map_height * TILE_SIZE, "Cub3d" );
    
    load_map(&game, av[1]);
    find_player(&game);
    load_images(&game);
    render_map(&game);
    user_input(&game);
    mlx_loop(game.mlx);
    return (0);
}

