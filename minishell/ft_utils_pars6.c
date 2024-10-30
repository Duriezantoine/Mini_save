/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 11:14:28 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 14:05:42 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	c;

	c = 0;
	while (s1[c] == s2[c] && (s1[c] != '\0' && s2[c] != '\0'))
		c++;
	return (s1[c] - s2[c]);
}

int	ft_split_with_space(t_echo *data_echo, char *input)
{
	if (ft_init_token_space(data_echo, input, 0) == 1)
		return (1);
	ft_init_echo_malloc(data_echo);
	ft_init_tab_echo_malloc(data_echo, input, 0);
	ft_insert_tab_echo(data_echo, input, 0);
	return (0);
}

void	ft_insert_data_data_echo_w(t_save **save, t_echo *data_echo,
		int iterateur_w)
{
	t_save	*new_node;
	t_save	*current;

	new_node = malloc(sizeof(t_save));
	if (!new_node)
		return ;
	new_node->str = malloc(sizeof(char)
			* ft_strlen(data_echo->str_w_quot[iterateur_w].str) + 1);
	if (!new_node->str)
	{
		free(new_node);
		return ;
	}
	ft_strcpy(new_node->str, data_echo->str_w_quot[iterateur_w].str);
	new_node->bool = data_echo->str_w_quot[iterateur_w].bool;
	new_node->next = NULL;
	if (*save == NULL)
		*save = new_node;
	else
	{
		current = *save;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	ft_insert_data_data_echo_s(t_save **save, t_echo *data_echo,
		int iterateur_s, t_env *env)
{
	t_save	*new_node;
	t_save	*current;

	new_node = ft_calloc(sizeof(t_save), 1);
	(void)env;
	if (!new_node)
		return ;
	new_node->str = ft_strdup(data_echo->str_s_quot[iterateur_s].str);
	data_echo->str_s_quot[iterateur_s].order = -2;
	new_node->bool = data_echo->str_s_quot[iterateur_s].bool;
	new_node->next = NULL;
	if (*save == NULL)
		*save = new_node;
	else
	{
		current = *save;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	ft_insert_new_data_with_data(t_save **save, t_echo *data_echo,
		t_env *env)
{
	int	i;
	int	iterateur_w;
	int	iterateur_s;

	(void)data_echo;
	i = -1;
	while (++i < data_echo->w_quot + data_echo->s_quot)
	{
		iterateur_s = 0;
		while (iterateur_s < data_echo->s_quot)
		{
			if (data_echo->str_s_quot[iterateur_s].order == i)
				ft_insert_data_data_echo_s(save, data_echo, iterateur_s, env);
			iterateur_s++;
		}
		iterateur_w = 0;
		while (iterateur_w < data_echo->w_quot)
		{
			if (data_echo->str_w_quot[iterateur_w].order == i)
				ft_insert_data_data_echo_w(save, data_echo, iterateur_w);
			iterateur_w++;
		}
	}
}
