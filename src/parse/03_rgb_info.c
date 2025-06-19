/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_rgb_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:08:06 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/19 18:34:48 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void add_fl_and_c(t_game *game, char *line)
{
	int		i;
	int		f_val;
	int		s_val;
	int		t_val;
	bool	ch;
	
	i = 0;
	ch = false;
	while (!ft_strchr(NB, line[i]))
		i++;
	f_val = get_rgb_val(line, &i);
	while (!ft_strchr(NB, line[i]))
	{
		if (!ft_strchr(WS, line[i]) && line[i] != ',')
		{
			ft_printf(RED ERR RGB RESET);
			close_and_free(game, 2);	
		}
		if (!ch && line[i] == ',')
			ch = true;
		else if (ch && line[i] == ',')
		{
			ft_printf(RED ERR RGB RESET);
			close_and_free(game, 2);	
		}
		i++;
	}
	ch = false;
	s_val = get_rgb_val(line, &i);
	while (!ft_strchr(NB, line[i]))
	{
		if (!ft_strchr(WS, line[i]) && line[i] != ',')
		{
			ft_printf(RED ERR RGB RESET);
			close_and_free(game, 2);	
		}
		if (!ch && line[i] == ',')
			ch = true;
		else if (ch && line[i] == ',')
		{
			ft_printf(RED ERR RGB RESET);
			close_and_free(game, 2);
		}
		i++;	
	}
	t_val = get_rgb_val(line, &i);
	while (line[i])
	{
		if (!ft_strchr(WS, line[i]))
		{
			ft_printf(RED ERR RGB RESET);
			close_and_free(game, 2);	
		}
		i++;	
	}
	i = -1;
	while (line[++i])
	{
		if (line[i] == 'F')
		{
			game->map_inf.f_rgb = malloc(sizeof(int) * 3);
			i = 0;
			game->map_inf.f_rgb[0] = f_val;
			game->map_inf.f_rgb[1] = s_val;
			game->map_inf.f_rgb[2] = t_val;
			break;
		}
		if (line[i] == 'C')
		{
			game->map_inf.c_rgb = malloc(sizeof(int) * 3);
			i = 0;
			game->map_inf.c_rgb[0] = f_val;
			game->map_inf.c_rgb[1] = s_val;
			game->map_inf.c_rgb[2] = t_val;
			break;
		}
	}
}

int	get_rgb_val(char *line, int *start)
{
	char	*val_str;
	int		val;
	int		i;
	int		tmp;
	int		len;

	tmp = *start;
	i = 0;
	len = 0;
	while (ft_strchr(NB, line[tmp]))
	{
		len++;
		tmp++;
	}
	val_str = ft_calloc(len + 1, sizeof(char));
	while (ft_strchr(NB, line[*start]))
	{
		val_str[i] = line[*start];
		i++;
		(*start)++;
	}
	val_str[i] = '\0';
	val = ft_atoi(val_str);
	val_str = safe_free(val_str);
	return (val);
}
