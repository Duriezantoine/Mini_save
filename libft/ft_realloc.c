#include "libft.h"
#include <malloc.h>

char	*ft_realloc(char *ptr, size_t last, size_t new)
{
	char	*ret;

	ret = ft_calloc(new, sizeof(char));
	if (!ret)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr)
	{
		while (last > 0 && --last)
			ret[last] = ptr[last];
		ret[0] = ptr[0];
		free(ptr);
	}
	return (ret);
}
