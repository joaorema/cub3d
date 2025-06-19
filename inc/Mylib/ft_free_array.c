#include "libft.h"

void	ft_free_array(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (array[i])
			array[i] = safe_free(array[i]);
		i++;
	}
	array = safe_free(array);
	return ;
}