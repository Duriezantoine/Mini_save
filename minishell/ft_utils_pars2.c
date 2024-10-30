/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:13:52 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 14:06:14 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*allocate_token(char *str, int start, int end)
{
	char	*res;

	res = malloc(sizeof(char) * (end - start + 1));
	ft_strcpy(res, str + start);
	return (res);
}

static void	handle_pipe_char(char *str, char **tokens, int *i,
		t_split_data *data)
{
	str[*i] = '\0';
	tokens[data->count++] = allocate_token(str, data->j, *i);
	data->j = *i + 1;
}

static void	init_split_data(t_split_data *data)
{
	data->count = 0;
	data->j = 0;
	data->in_quotes = 0;
}

char	**split_string(char *str, int *len)
{
	char			**tokens;
	int				i;
	t_split_data	data;

	tokens = malloc(sizeof(char *) * 100);
	if (!tokens)
		return (NULL);
	i = 0;
	init_split_data(&data);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			data.in_quotes = !data.in_quotes;
		if (str[i] == '|' && !data.in_quotes)
			handle_pipe_char(str, tokens, &i, &data);
		i++;
	}
	tokens[data.count++] = allocate_token(str, data.j, i);
	*len = data.count;
	return (tokens);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	if (!src)
		return (NULL);
	i = ft_strlen(src);
	dest = (char *)ft_calloc(i + 1, sizeof(char));
	if (dest == 0)
		return (0);
	while (i-- != 0)
		dest[i] = src[i];
	return (dest);
}
