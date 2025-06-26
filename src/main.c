#include "../inc/cub3d.h"

int main(int ac, char *av[])
{
    t_game game;

    if (ac != 2)
    {
        ft_printf("Usage : %s <map_file> \n", av[0]);
        return (1); 
    }
    init(&game, av[1]);
    //render_rays(&game);                                             //display first render then update if move
    handle_keys(&game);
    loop(&game);
    return (0);
}
