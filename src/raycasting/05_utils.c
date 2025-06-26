/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:37:55 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 14:37:56 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

float distance(float ax, float ay, float bx, float by, float ang)
{
    (void)ang;
    return (sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)) );                      //soma do quadrado dos catetos
}

float clamptexture(float value, float min, float max)
{
    if (value < min) 
        return min;
    if (value > max) 
        return max;
    return value;
}

int clamp_point(int value, int min, int max)
{
    if (value < min) 
        return min;
    if (value > max) 
        return max;
    return value;
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

int create_trgb(int r, int g, int b)
{
    return (r << 16) | (g << 8) | b;
}
