#include "../../inc/cub3d.h"

void load_wall_images(t_game *game)                                                                          //loads the image into my game struct
{
    game->no_img.img = mlx_xpm_file_to_image(game->mlx, "images/blue.xpm",
                                         &game->no_img.width, &game->no_img.height);
    game->so_img.img = mlx_xpm_file_to_image(game->mlx, "images/rock_wall.xpm",
                                         &game->so_img.width, &game->so_img.height);
    game->we_img.img = mlx_xpm_file_to_image(game->mlx, "images/tijolo.xpm",
                                         &game->we_img.width, &game->we_img.height);
    game->ea_img.img = mlx_xpm_file_to_image(game->mlx, "images/madeira.xpm",
                                         &game->ea_img.width, &game->ea_img.height);
    game->no_img.addr = mlx_get_data_addr(game->no_img.img, &game->no_img.bits_per_pixel,
                                     &game->no_img.line_len, &game->no_img.endian);
    game->so_img.addr = mlx_get_data_addr(game->so_img.img, &game->so_img.bits_per_pixel,
                                     &game->so_img.line_len, &game->so_img.endian);
    game->we_img.addr = mlx_get_data_addr(game->we_img.img, &game->we_img.bits_per_pixel,
                                     &game->we_img.line_len, &game->we_img.endian);
    game->ea_img.addr = mlx_get_data_addr(game->ea_img.img, &game->ea_img.bits_per_pixel,
                                     &game->ea_img.line_len, &game->ea_img.endian); 
}

unsigned int get_texture(t_game *game, t_wall *wall, int y)
{
    int tex_y;
    int tex_x;
    int wall_height;
    char *pixel;
    float wall_y;
    t_image *texture;

    texture = set_side(game, wall);
    tex_x = wall->texture_x;
    wall_height = wall->bottom_pixel - wall->top_pixel;
    wall_y = (float)(y - wall->top_pixel) / (float)wall_height;
    wall_y = clamptexture(wall_y, 0.0f, 1.0f);
    tex_y = (int)(wall_y * (texture->height - 1));
    tex_x = clamp_point(tex_x, 0, texture->width);
    tex_y = clamp_point(tex_y, 0, texture->height);
    pixel = texture->addr + (tex_y * texture->line_len + tex_x * (texture->bits_per_pixel / 8));
    return *(unsigned int *)pixel;
}

t_image *set_side(t_game *game, t_wall *wall)
{
    if (wall->side == NORTH)
        return &game->no_img;
    else if (wall->side == SOUTH)
        return &game->so_img;
    else if (wall->side == WEST)
        return &game->we_img;
    else if (wall->side == EAST)
        return &game->ea_img;
     return NULL;
}