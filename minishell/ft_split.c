/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:46:30 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/08 15:30:11 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_nb_words(char const *s, char c)
{
	size_t	nb;
	size_t	i;

	nb = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (i == 0 || s[i - 1] == c)
				nb++;
		}
		i++;
	}
	return (nb);
}

static int	ft_wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	ft_free_tab_tab(char **res)
{
	size_t	i;

	i = 0;
	while (res[i] != 0)
		free(res[i++]);
	free(res);
}

static char	**ft_fill_res(char const *s, char c, char **res)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (i == 0 || s[i - 1] == c)
			{
				res[j] = ft_calloc((ft_wordlen(s + i, c) + 1), sizeof(char));
				if (res[j++] == NULL)
				{
					ft_free_tab_tab(res);
					return (NULL);
				}
				k = 0;
			}
			res[j - 1][k++] = s[i];
		}
		i++;
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	nb_words;

	if (s == NULL)
		return (NULL);
	nb_words = ft_get_nb_words(s, c);
	if (nb_words == 0)
	{
		res = malloc(sizeof(char *));
		res[0] = 0;
		return (res);
	}
	res = ft_calloc((nb_words + 1), sizeof(char *));
	if (res == NULL)
		return (res);
	return (ft_fill_res(s, c, res));
}
