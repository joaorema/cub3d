#include "libft.h"

void	*safe_free(void *ptr)
{
	if (!ptr)
		return (NULL);
	if (ptr)
		free(ptr);
	return (NULL);
}