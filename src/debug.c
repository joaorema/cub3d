
#include "../inc/cub3d.h"

void	print_map_info(t_game *game)
{
	int i = -1;

	ft_printf("Map height: %d\n", game->map_height);
	ft_printf("Map width: %d\n", game->map_width);
	if (game->map_inf.no_pth)
		ft_printf("north is: %s\n", game->map_inf.no_pth);
	if (game->map_inf.so_pth)
		ft_printf("south is: %s\n", game->map_inf.so_pth);
	if (game->map_inf.ea_pth)
		ft_printf("east is: %s\n", game->map_inf.ea_pth);
	if (game->map_inf.we_pth)
		ft_printf("west is: %s\n", game->map_inf.we_pth);
	if (game->map_inf.f_rgb)
		ft_printf("floor is: %d, %d, %d\n", game->map_inf.f_rgb[0], game->map_inf.f_rgb[1], game->map_inf.f_rgb[2]);
	if (game->map_inf.c_rgb)
		ft_printf("ceiling is: %d, %d, %d\n", game->map_inf.c_rgb[0], game->map_inf.c_rgb[1], game->map_inf.c_rgb[2]); //debug to delete
	while (++i < game->map_height)
		ft_printf("%s\n", game->map[i]);
}