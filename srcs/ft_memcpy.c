#include "includes/malloc.h"
 
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	char			*str;
	const	char	*s;

	i = 0;
	str = (char*)dest;
	s = (char*)src;
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	return (str);
}