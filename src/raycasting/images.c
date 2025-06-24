#include "../../inc/cub3d.h"

void load_wall_image(t_game *game)                                                                          //loads the image into my game struct
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

unsigned int get_texture(t_game *game, t_wall *wall, int y)                                                 //gets the texture from the image
{
    int tex_y;
    int tex_x;
    int wall_height;
    char *pixel;
    float wall_y;

    tex_x = wall->texture_x;                                                                                       //horizontal coordinate
    wall_height = wall->bottom_pixel - wall->top_pixel;                                                            //height of the wall slice on the screen.
    if (wall_height <= 0)
        return 0;
    wall_y = (float)(y - wall->top_pixel) / (float)wall_height;                                                   
    wall_y = clamptexture(wall_y, 0.0f, 1.0f);                                                                     //ensure its withing [0.0, 1.0]
    tex_y = (int)(wall_y * (game->wall_img.height - 1));                                                           //vertical coordinate
    tex_x = clamp_point(tex_x, 0, game->wall_img.width);                                                           //center the pixel in x
    tex_y = clamp_point(tex_y, 0, game->wall_img.height);                                                          //center the pixel in y
    pixel = game->wall_img.addr + (tex_y * game->wall_img.line_len + tex_x * (game->wall_img.bits_per_pixel / 8)); //returns 1 pixel from loaded image
    return *(unsigned int *)pixel;
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)                                                //puts a pixel at a specific coordinate
{
    char *dst;

    if (x < 0 || y < 0 || x > img->width || y > img->height)
        return;
    dst = img->addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw(t_image *image, t_point pos, t_point size, int color)                                          //used to draw the full wall
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
			my_mlx_pixel_put(image, pos.x + x, pos.y + y++, color);
		x++;
	}
}
