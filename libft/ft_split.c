/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 11:06:20 by tdelage           #+#    #+#             */
/*   Updated: 2023/11/15 14:21:03 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <malloc.h>

static int	ft_strlen_delim(char *str, char charset)
{
	int	i;

	i = 0;
	while (i[str])
	{
		if (i[str] == charset)
			return (i);
		i++;
	}
	return (i);
}

static char	**count_substr(char *str, char set, int *n)
{
	int	i;
	int	cnt;
	int	nb;

	i = 0;
	cnt = 1;
	nb = 0;
	while (i[str])
	{
		if (i[str] == set)
			cnt = 1;
		else if (cnt)
		{
			nb++;
			cnt = 0;
		}
		i++;
	}
	*n = nb;
	return ((char **)ft_calloc(nb + 1, sizeof(char *)));
}

static void	*ft_free_split(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return (NULL);
	while (split[i])
	{
		if (split[i])
			free(split[i]);
	}
	free(split);
	return (NULL);
}

static int	get_next_tok(char *str, char set, size_t k, int *cnt_word)
{
	int	i;

	if (cnt_word)
		(*cnt_word)++;
	i = 0;
	while (i[str] && i[str] == set)
		i++;
	return (i + k);
}

char	**ft_split(char const *str, char charset)
{
	char	**split;
	size_t	off;
	size_t	k;
	int		inb[2];

	off = 0;
	k = 0;
	(inb[0]) = 0;
	inb[1] = 0;
	if (str == NULL)
		return (NULL);
	split = count_substr((char *)str, charset, &(inb[1]));
	if (split == NULL)
		return (NULL);
	off = get_next_tok((char *)str, charset, 0, NULL);
	while ((inb[0]) < inb[1])
	{
		k = ft_strlen_delim((char *)str + off, charset);
		(inb[0])[split] = ft_substr(str, off, k);
		if ((inb[0])[split] == NULL)
			return ((char **)ft_free_split(split));
		off += get_next_tok((char *)str + off + k, charset, k, &(inb[0]));
	}
	(inb[0])[split] = NULL;
	return (split);
}
