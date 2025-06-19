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
    render_rays(game);
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
                game->player_tile_x = x;
                game->player_tile_y = y;
                game->player_x = x * TILE_SIZE + TILE_SIZE / 2;
                game->player_y = y * TILE_SIZE + TILE_SIZE / 2;
                return;
            }
            x++;
        }
        y++;
    }
    exit(1); //if not found
}

void update_game(t_game *game)
{
    if (game->map[game->player_y][game->player_x] == '0')
		game->map[game->player_y][game->player_x] = 'P';
}
