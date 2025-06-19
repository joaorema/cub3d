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
    draw_line(game);
    horizontal_check(game, NULL);
    vertical_check(game, NULL);
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

