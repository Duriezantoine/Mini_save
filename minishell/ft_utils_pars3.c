/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:14:09 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 14:24:54 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_bzero(void *s, size_t n)
{
	return (ft_memset(s, 0, n));
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned long	i;
	unsigned char	*t;

	t = (unsigned char *)s;
	i = 0;
	while (i != n)
		t[i++] = c;
	return (s);
}

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	size_t	mem_size;
	void	*mem_init;

	if (elementCount <= 0 || elementSize <= 0)
		return (malloc(0));
	if ((long long)elementCount < 0 || (long long)elementSize < 0)
		return (0);
	mem_size = elementCount * elementSize;
	mem_init = malloc(mem_size);
	if (!(mem_init))
		return (NULL);
	return (ft_bzero(mem_init, mem_size));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_dest;
	size_t	len_dest;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	len_dest = (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	str_dest = (char *)ft_calloc(len_dest, 1);
	if (str_dest == 0)
		return (0);
	i = 0;
	while (*s1 != 0)
	{
		str_dest[i] = *s1++;
		i++;
	}
	while (*s2 != 0)
	{
		str_dest[i] = *s2++;
		i++;
	}
	str_dest[i] = 0;
	return (str_dest);
}
