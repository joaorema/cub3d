/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_load_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:33 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/25 18:40:56 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_line_len(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		len--;
	if (len > 0 && line[len - 1] == '\r')
		len--;
	return (len);
}

int	safe_fd_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf(RED ERR OP RESET);
		return (-1);
	}
	return (fd);
}

int	is_map(char *line)
{
	int		i;
	char	c;
	char	n;

	i = 0;
	if (line[i] == '\n')
		return (0);
	while (line[i] && ft_strchr(WS, line[i]))
		i++;
	if (!line[i])
		return (0);
	c = line[i];
	if ((line[i] != '\0') && (line[i + 1] != '\0'))
		n = line[i + 1];
	else
		n = '\0';
	if (ft_strchr(CH_MAP, c) && ((n == '\0') || ft_strchr(N_CH_MAP, n)))
	{
		if (c == 'W' && ((n != '\0') && n == 'E'))
			return (0);
		return (1);	
	}
	return (0);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return(0);
	while (line[i])
	{
		if (!ft_strchr(WS, line[i]))
			return(0);
		i++;
	}
	return (1);
}
