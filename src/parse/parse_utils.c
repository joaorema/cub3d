/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:33 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/20 10:59:57 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


void count_width(t_game *game, char *file)
{
    int fd;
    int max_len;
    char *line;
    int len;

    max_len = 0;
    fd = open(file, O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            len--; // Exclude newline
        if (len > max_len)
            max_len = len;
        free(line);
    }
    close(fd);
    game->map_width = max_len;
}

void count_height(t_game *game, char *file)
{
    int fd;
    int counter;
    char *line;

    counter = 0;
    fd = open(file, O_RDONLY);
    if (fd < 0 || ft_strcmp(file + (ft_strlen(file) - 4), ".cub"))                    //check if the file end with .cub
    {
        ft_printf("something went wrong with the file\n");
        exit (1);
    }
    while((line = get_next_line(fd)) != NULL)
    {
        counter++;
        free(line);
    }
    game->map_height = counter;
    free(line);
    close(fd);
}
    