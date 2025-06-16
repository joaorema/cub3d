/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:00:02 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/10 16:27:09 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

t_game  start_game(t_game *game)
{
    game->map = NULL;
    game->temp_map = NULL;
    game->player = 0;
    game->player_x = 0;
    game->player_y = 0;
    game->map_width = 0;
    game->map_height = 0;
    game->mlx = mlx_init();
    game->win = NULL;
    return (*game);

}

void load_images(t_game *game)
{
    int image_w;
    int image_h;

    game->wall = mlx_xpm_file_to_image(game->mlx, "images/wall.xpm", &image_w, &image_h);
    game->player_img = mlx_xpm_file_to_image(game->mlx, "images/player.xpm", &image_w, &image_h);
    if(!game->player_img || !game->wall)
    {   
        ft_putstr_fd("Error loading images\n", 2);
        return ;
    }
    
}

int	handle_keyboard(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(1);
	if (keycode == 119 || keycode == 65362)
		player_move(game, 0, -1);
	if (keycode == 115 || keycode == 65364)
		player_move(game, 0, 1);
	if (keycode == 97 || keycode == 65361)
		player_move(game, -1, 0);
	if (keycode == 100 || keycode == 65363)
		player_move(game, 1, 0);
	return (0);
}

void	player_move(t_game *game, int dx, int dy)
{
    int new_x;
    int new_y;

    new_x = game->player_x + dx;
    new_y = game->player_y + dy;
    

    game->map[game->player_y][game->player_x] = '0';
    game->player_x = new_x;
    game->player_y = new_y;

    game->map[new_y][new_x] = 'P';

    mlx_clear_window(game->mlx, game->win);
    render_map(game);
}

void	user_input(t_game *game)
{
	mlx_key_hook(game->win, handle_keyboard, game);
    
}

void update_game(t_game *game)
{
    if (game->map[game->player_y][game->player_x] == '0')
		game->map[game->player_y][game->player_x] = 'P';
}

/*
void update_player(t_game *game)
{
    mlx_clear_window(game->mlx, game->win);    //clear window
    mlx_put_image_to_window(game->mlx, game->win, game->player_img, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}
*/

void load_map(t_game *game, char *file)
{
    int fd;
    int i;
    char *temp;

    count_height(game, file);
    count_width(game, file);
    fd = open(file, O_RDONLY);
    game->map = ft_calloc(game->map_height + 1, sizeof(char *));
    game->temp_map = ft_calloc(game->map_height + 1, sizeof(char *));
    if(!game->map || !game->temp_map)
    {
        ft_putstr_fd("Failed to allocate space for map\n", 2);
        exit (1);
    }
    i = 0;
    while(i < game->map_height)
    {
        temp = get_next_line(fd);
        game->map[i] = ft_strtrim(temp, "\n");
        free(temp);
        game->temp_map[i] = ft_strdup(game->map[i]);
        i++;
    }
    close(fd);
}

void render_images(t_game *game, int x, int y)
{
    if(game->map[y][x] == '1')
        mlx_put_image_to_window(game->mlx, game->win, game->wall, x * TILE_SIZE, y * TILE_SIZE);
    else if(game->map[y][x] == 'P')
        mlx_put_image_to_window(game->mlx, game->win, game->player_img, x * TILE_SIZE, y * TILE_SIZE);
}

void render_map(t_game *game)
{
    int x;
    int y;

    y = 0;
    while(y < game->map_height)
    {
        x = 0;
        while(x < game->map_width)
        {
            render_images(game, x, y);
            x++;
        }
        y++;
    }   
}

void find_player(t_game *game)
{
    int x;
    int y;

    y = 0;
    while(y < game->map_height)
    {
        x = 0;
        while(x < game->map_width)
        {
            if(game->map[y][x] == 'P')
            {
                game->player_y = y;
                game->player_x = x;
                return;
            }
            x++;
        }
        y++;
    }
    exit(1); //if not found
}