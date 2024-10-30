/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_pars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:51:14 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/29 16:39:51 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exit_codes(char **str, t_data *data)
{
	char	*tmp_tmp;
	char	*tmp_save;

	tmp_tmp = ft_itoa(data->exit_code);
	tmp_save = ft_strjoin(tmp_tmp, *str + 2);
	free(tmp_tmp);
	*str = tmp_save;
	return (ft_strlen(tmp_tmp));
}

int	ft_insert_env_var(char **str, char *var, char **after, int i)
{
	int	diff_size;

	if (var == NULL)
	{
		if (((*after)[0] != 0 || i != 1))
		{
			*str = *after;
			*after = NULL;
			diff_size = 0;
		}
		else
		{
			diff_size = 1;
			*str = ft_strjoin("$", *after);
		}
	}
	else
	{
		*str = ft_strjoin(var, *after);
		diff_size = ft_strlen(var);
	}
	return (diff_size);
}

int	ft_change_var_environnement(char **str, t_env *env, t_data *data)
{
	int		i;
	char	*after;
	char	*var;
	int		diff_size;

	if ((*str)[1] == '?')
		return (handle_exit_codes(str, data));
	i = 1;
	while (((*str)[i] >= 'a' && (*str)[i] <= 'z')
			|| ((*str)[i] >= 'A' && (*str)[i] <= 'Z')
			|| (*str)[i] == '_'
			|| (i != 1 && (*str)[i] >= '0' && (*str)[i] <= '9'))
		i++;
	after = ft_strdup((*str) + i);
	(*str)[i] = 0;
	var = find_env_value((*str) + 1, env);
	diff_size = ft_insert_env_var(str, var, &after, i);
	free(after);
	free(var);
	return (diff_size);
}

static void	handle_current_char(char *input, int *i, int *ss_quot, int *wt_quot)
{
	if ((input[*i] == '"' || input[*i] == '\''))
	{
		if (input[*i + 1] != input[*i])
			ft_handle_quotes(input, i, wt_quot, input[*i]);
		else
		{
			(*i)++;
			if (input[*i] != '\0')
				(*i)++;
		}
	}
	if (input[*i] == '<' || input[*i] == '>')
		ft_handle_redirection(input, i, ss_quot);
	if (ft_isalnum(input[*i]) && !ft_white_space(input[*i]))
		ft_handle_alphanumeric(input, i, ss_quot, 1);
}

int	ft_init_token_space(t_echo *data_echo, char *input, int i)
{
	int	ss_quot;
	int	wt_quot;

	ss_quot = 0;
	wt_quot = 0;
	while (input[i])
	{
		while (ft_white_space(input[i]))
			i++;
		handle_current_char(input, &i, &ss_quot, &wt_quot);
		if (check_end_of_input(input[i], data_echo, &ss_quot, &wt_quot))
			break ;
		if (ft_white_space(input[i]))
			i++;
	}
	data_echo->s_quot = ss_quot;
	data_echo->w_quot = wt_quot;
	return (0);
}
