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
    game = start_game(&game);
    count_width(&game, av[1]);
    count_height(&game, av[1]);
    ft_printf("Map width: %d\n", game.map_width);
    ft_printf("Map height: %d\n", game.map_height);
    return (0);
    
}