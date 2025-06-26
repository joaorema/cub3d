/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_cub.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:33:58 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/26 19:25:31 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gnl_free_fd(int fd)
{
	t_gnllist	**list;

	list = get_gnl_list();
	if (fd < 0 || fd >= MAX_FD || !list[fd])
		return ;
	ft_clear_list(&list[fd]);
	list[fd] = NULL;
}

t_gnllist	**get_gnl_list(void)
{
	static t_gnllist	*list[MAX_FD];

	return (list);
}

void	ft_clear_list(t_gnllist **list)
{
	t_gnllist	*tmp;

	if (!list || !*list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->str_buff)
			free((*list)->str_buff);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}
