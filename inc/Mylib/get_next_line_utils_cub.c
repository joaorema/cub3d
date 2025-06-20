/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_cub.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:33:58 by icunha-t          #+#    #+#             */
/*   Updated: 2025/06/20 12:38:38 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gnl_free_fd(int fd)
{
	t_gnllist **list;
	
	list = get_gnl_list();
	if (fd < 0 || fd >= MAX_FD || !list[fd])
		return;
	ft_clear_list(&list[fd]);
	list[fd] = NULL;
}

t_gnllist	**get_gnl_list(void)
{
	static t_gnllist	*list[MAX_FD];

	return (list);
}
