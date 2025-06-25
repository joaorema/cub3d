/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_rgb_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isabel <isabel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:08:06 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 00:10:46 by isabel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	add_f_and_c(t_game *game, t_gnl gnl)
{
	int		i;
	t_rgb	rgb;
	bool	ch;
	
	i = 0;
	ch = false;
	while (!ft_strchr(NB, gnl.line[i]))
	{
		if (gnl.line[i] != 'F' && gnl.line[i] != 'C' && !ft_strchr(WS, gnl.line[i]))
			print_err_and_exit(game, RED ERR RGB RESET, 2, &gnl);
		i++;	
	}
	rgb.f_val = get_rgb_val(game, gnl, &i);
	ch_mid_val(game, gnl, &i, &ch);
	ch = false;
	rgb.s_val = get_rgb_val(game, gnl, &i);
	ch_mid_val(game, gnl, &i, &ch);
	rgb.t_val = get_rgb_val(game, gnl, &i);
	while (gnl.line[i])
	{
		if (!ft_strchr(WS, gnl.line[i++]))
			print_err_and_exit(game, RED ERR RGB RESET, 2, &gnl);
	}
	set_rgb_f(game, gnl, rgb);
	set_rgb_c(game, gnl, rgb);
}

int	get_rgb_val(t_game *game, t_gnl gnl, int *start)
{
	char	*val_str;
	int		val;
	int		i;
	int		tmp;
	int		len;

	tmp = *start;
	i = 0;
	len = 0;
	if (gnl.line[*start] == '\0')
		print_err_and_exit(game, RED ERR RGB RESET, 2, &gnl);
	while (ft_strchr(NB, gnl.line[tmp++]))
		len++;
	val_str = ft_calloc(len + 1, sizeof(char));
	while (ft_strchr(NB, gnl.line[*start]))
		val_str[i++] = gnl.line[(*start)++];
	val_str[i] = '\0';
	val = ft_atoi(val_str);
	val_str = safe_free(val_str);
	if (val < 0 || val > 255)
		print_err_and_exit(game, RED ERR RGB RESET, 2, &gnl);
	return (val);
}

void	ch_mid_val(t_game *game, t_gnl gnl, int *i, bool *ch)
{
	while (!ft_strchr(NB, gnl.line[*i]))
	{
		if (!ft_strchr(WS, gnl.line[*i]) && gnl.line[*i] != ',')
			print_err_and_exit(game, RED ERR RGB RESET, 2, &gnl);
		if (!*ch && gnl.line[*i] == ',')
			*ch = true;
		else if (*ch && gnl.line[*i] == ',')
			print_err_and_exit(game, RED ERR RGB RESET, 2, &gnl);
		(*i)++;
	}
} 

void	set_rgb_f(t_game *game, t_gnl gnl, t_rgb rgb)
{
	int			i;
	static bool	ch_f;

	i = -1;
	while (gnl.line[++i])
	{
		if (gnl.line[i] == 'F')
		{
			if (ch_f)
				print_err_and_exit (game, RED ERR DPINF RESET, 2, &gnl);
			ch_f = true;
			game->map_inf.f_rgb = ft_calloc(3, sizeof(int));
			i = 0;
			game->map_inf.f_rgb[0] = rgb.f_val;
			game->map_inf.f_rgb[1] = rgb.s_val;
			game->map_inf.f_rgb[2] = rgb.t_val;
			break;
		}
	}
}

void	set_rgb_c(t_game *game, t_gnl gnl, t_rgb rgb)
{
	int			i;
	static bool	ch_c;

	i = -1;
	while (gnl.line[++i])
	{
		if (gnl.line[i] == 'C')
		{
			if (ch_c)
				print_err_and_exit (game, RED ERR DPINF RESET, 2, &gnl);
			ch_c = true;
			game->map_inf.c_rgb = ft_calloc(3, sizeof(int));
			i = 0;
			game->map_inf.c_rgb[0] = rgb.f_val;
			game->map_inf.c_rgb[1] = rgb.s_val;
			game->map_inf.c_rgb[2] = rgb.t_val;
			break;
		}
	}
}
