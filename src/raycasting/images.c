#include "../../inc/cub3d.h"


void load_wall_image(t_game *game, t_image *texture)
{
    texture->img = mlx_xpm_file_to_image(game->mlx, "../images/wall.xpm",
                                        &texture->width, &texture->height);
    if(!texture->img)
        exit(2);
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
                                    &texture->line_len, &texture->endian);
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;
    dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}