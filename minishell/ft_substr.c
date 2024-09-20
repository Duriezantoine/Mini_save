/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:32:27 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/28 17:39:07 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_check_input(char const *s, unsigned int start, size_t len)
{
	if (start > (size_t)ft_strlen(s))
		return (len = 0);
	if (len > (size_t)ft_strlen(s) - start)
		return (len = ((size_t)ft_strlen(s)) - start);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	size = ft_check_input(s, start, len);
	ptr = malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			ptr[j] = s[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}
