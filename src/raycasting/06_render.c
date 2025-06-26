/* ************************************************************************** */
/*									                                        */
/*                                                        :::      ::::::::   */
/*   04_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:36:51 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 14:37:02 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	render_rays(t_game *game)
{
	int		i;
	float	ray_angle;

	i = 0;
	ray_angle = game->player_angle - (FOV / 2);
	while (i < NUM_RAYS)
	{
		render_wall(game, ray_angle, i);
		ray_angle += ANGLE_STEP;
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		if (ray_angle > 2 * PI)
			ray_angle -= 2 * PI;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

void	render_wall(t_game *game, float angle, int ray_index)
{
	t_rayhit	v_hit;
	t_rayhit	h_hit;
	t_rayhits	new_hit;
	t_wall		wall;

	init_rayhit(&v_hit, game, angle);
	init_rayhit(&h_hit, game, angle);
	horizontal_check(game, &h_hit);
	vertical_check(game, &v_hit);
	wall.screen_x = (ray_index);
	wall.slice_width = 1;
	new_hit.h_hit = h_hit;
	new_hit.v_hit = v_hit;
	init_wall(game, &new_hit, &wall, angle);
	draw_topbottom(game, &wall);
	draw_wall_slice(game, &wall);
}

void	draw_topbottom(t_game *game, t_wall *wall)
{
	int	x;
	int	w;
	int	sky_height;
	int	floor_height;

	x = wall->screen_x;
	w = 0;
	while (w < wall->slice_width)
	{
		sky_height = (int)wall->top_pixel;
		floor_height = game->win_height - (int)wall->bottom_pixel;
		if (sky_height > 0)
			draw(&game->img, (t_point){x + w, 0}, (t_point){1, sky_height},
				game->sky_color);
		if (floor_height > 0)
			draw(&game->img, (t_point){x + w, (int)wall->bottom_pixel},
				(t_point){1, floor_height}, game->floor_color);
		w++;
	}
}

void	draw_wall_slice(t_game *game, t_wall *wall)
{
	int				y_start;
	int				y_end;
	int				y;
	t_point			pos;
	unsigned int	color;

	pos.x = wall->screen_x;
	pos.y = 0;
	y_start = (int)wall->top_pixel;
	y_end = (int)wall->bottom_pixel;
	if (y_start >= y_end)
		return ;
	while (pos.y < wall->slice_width)
	{
		y = y_start;
		while (y < y_end)
		{
			color = get_texture(game, wall, y);
			my_mlx_pixel_put(&game->img, pos.x + pos.y, y, color);
			y++;
		}
		pos.y++;
	}
}

int	create_trgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
