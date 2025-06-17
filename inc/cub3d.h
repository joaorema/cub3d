/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:51:10 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/17 18:41:37 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "Mylib/libft.h"
#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <unistd.h>

# define RESET  "\033[0m"
# define RED    "\033[1;31m"
# define GREEN  "\033[1;32m"
# define BLUE   "\033[1;36m"

typedef struct s_position
{
    int x;
    int y;
    
} t_position;

typedef struct s_game
{
    void	*mlx;
    void	*win;
    char	**map;
    char	**tmp_map;
    int 	player;
    int		player_x;
    int		player_y;
    int		map_width;
    int		map_height;
    
} t_game;

int main(int ac, char *av[]);

//init
void  init_game(t_game *game);

//parse
void	ch_and_load_map(t_game *game, char *file);
int		ch_file(char *file, int fd);

//parse_utils
void	set_width(t_game *game, int fd);
void	set_height(t_game *game, int fd);

//close
void	close_and_free(t_game *game, int exit_code);
void	free_game(t_game *game);

#endif