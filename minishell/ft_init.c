/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/29 10:26:16 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data_list(t_node **list)
{
	*list = malloc(sizeof(t_node));
	if (list == NULL)
	{
		write(2, "Memory allocation failed for data\n",
			ft_strlen("Memory allocation failed for data\n"));
		exit(1);
	}
	(*list)->arg = NULL;
	(*list)->cmd = NULL;
	(*list)->env = NULL;
	(*list)->pipe[0] = -1;
	(*list)->prev = NULL;
	(*list)->next = NULL;
}

void	ft_init_data(t_data *data)
{
	data->nbr_command = 0;
	data->count = '1';
	data->bool = 0;
}

void	ft_init_echo_malloc(t_echo *data_echo)
{
	data_echo->str_w_quot = malloc(data_echo->w_quot * sizeof(t_str));
	data_echo->str_s_quot = malloc(data_echo->s_quot * sizeof(t_str));
}

t_arg	*ft_init_list(t_node *list, t_echo *data_echo, t_save *save)
{
	t_arg	*new_node;

	(void)data_echo;
	new_node = ft_calloc(sizeof(t_arg), 1);
	if (!new_node)
	{
		printf("Erreur d'allocation de mémoire\n");
		return (NULL);
	}
	new_node->str_command = ft_strdup(save->str);
	new_node->quot = save->bool;
	new_node->type = -1;
	if (!new_node->str_command)
	{
		printf("String duplication error\n");
		free(new_node);
		return (NULL);
	}
	if (list == NULL)
		printf("String duplication error\n");
	ft_insert_nodes(list, new_node);
	return (list->arg);
}

void	ft_insert_nodes(t_node *list, t_arg *new_node)
{
	t_arg	*tmp;

	if (list->arg == NULL)
	{
		list->arg = new_node;
		list->arg->prev = NULL;
	}
	else
	{
		tmp = list->arg;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new_node;
		new_node->prev = tmp;
	}
}
