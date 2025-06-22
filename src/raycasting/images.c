#include "../../inc/cub3d.h"


void load_wall_image(t_game *game)
{
    game->wall_img.img = mlx_xpm_file_to_image(game->mlx, "images/madeira.xpm",
                                         &game->wall_img.width, &game->wall_img.height);
    if(!game->wall_img.img)
    {
        ft_putstr_fd("Failed to load img", 2);
        exit(2);
    }
    game->wall_img.addr = mlx_get_data_addr(game->wall_img.img, &game->wall_img.bits_per_pixel,
                                     &game->wall_img.line_len, &game->wall_img.endian);
    
    if(!game->wall_img.addr)
    {
        ft_putstr_fd("Failed to set address", 2);
        exit(2);
    }   
}
    


void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x > img->width || y > img->height)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}