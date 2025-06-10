/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaorema <joaorema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:49:33 by joaorema          #+#    #+#             */
/*   Updated: 2025/06/10 16:41:04 by joaorema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"


void count_width(t_game *game, char *file)
{
    int fd;
    char *line;

    fd = open(file, O_RDONLY);
    if (fd < 0 || ft_strcmp(file + (ft_strlen(file) - 4), ".cub"))                    //check if the file end with .cub
    {
        ft_printf(RED "something went wrong with the file\n" RESET);
        exit (1);
    }
    line = get_next_line(fd);
    if(!line)
    {
        ft_printf(RED "Error: Empty file or unable to read\n" RESET);
        close(fd);
        exit(2);
    }
    while(line != NULL)
    {
        line = get_next_line(fd);
        game->map_width++;
    }
    free(line);
    close(fd);
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
        ft_printf(RED "something went wrong with the file\n" RESET);
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
    