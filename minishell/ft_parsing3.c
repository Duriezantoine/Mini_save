/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:55:22 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/29 15:12:18 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_chars_without_c(char *str, char c)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (str[x])
	{
		if (str[x] == c)
			x++;
		else
		{
			i++;
			x++;
		}
	}
	return (i);
}

char	*create_filtered_str(char *str, char c, int len)
{
	char	*save;
	int		i;
	int		x;

	save = malloc(sizeof(char) * (len + 1));
	if (!save)
		return (NULL);
	i = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == c)
			x++;
		else
		{
			save[i] = str[x];
			i++;
			x++;
		}
	}
	save[i] = '\0';
	return (save);
}

char	*ft_change_save_v3(char *str, t_env *env, char c, t_data *data)
{
	char	*save;
	int		len;

	save = NULL;
	(void) env;
	(void) data;
	len = count_chars_without_c(str, c);
	free(save);
	save = create_filtered_str(str, c, len);
	return (save);
}
