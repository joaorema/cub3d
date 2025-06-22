#include "../../inc/cub3d.h"

void load_map(t_game *game, char *file)
{
    int fd;
    int i;
    char *temp;

    count_height(game, file);
    count_width(game, file);
    fd = open(file, O_RDONLY);
    game->map = ft_calloc(game->map_height + 1, sizeof(char *));
    if(!game->map)
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
        i++;
    }
    close(fd);
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
                game->player.tile_x = x;
                game->player.tile_y = y;
                game->player.position.x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player.position.y = y * TILE_SIZE + TILE_SIZE / 2;
                return;
            }
            x++;
        }
        y++;
    }
    exit(1);
}
void render_map(t_game *game)   
{
    //mlx_clear_window(game->mlx, game->win);
    render_rays(game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int game_loop(t_game *game)
{
    render_map(game);
    return 0;
}