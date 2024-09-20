/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 13:35:06 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/24 12:47:10 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_str(char *src1, char *src2)
{
	char	*result;
	int		c;
	int		d;
	int		len;

	c = 0;
	d = 0;
	if (src1 == NULL || src2 == NULL)
		return (NULL);
	len = ft_strlen(src1) + ft_strlen(src2);
	result = malloc(sizeof(*result) * len + 1);
	if (result == NULL)
		return (NULL);
	while (c < (int)ft_strlen(src1))
	{
		result[c] = src1[c];
		c++;
	}
	while (c < (int)(ft_strlen(src1) + ft_strlen(src2)))
		result[c++] = src2[d++];
	result[c] = '\0';
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*src1;
	char	*src2;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	src1 = (char *)s1;
	src2 = (char *)s2;
	result = (get_str(src1, src2));
	return (result);
}
