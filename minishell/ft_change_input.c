/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_input.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:51:31 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 17:01:24 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_change_input_loop(char *var, t_env *env,
                                t_data *data, char **save_tmp)
{
	char *save;
	char *tmp_tmp;
    
    if (ft_space_or_null(var)!=0)
    {
        if (var[0]== '$')
        {
            tmp_tmp = ft_change_var_environnement(var, &env, data);
            var = tmp_tmp;
        }
        save = ft_strjoin(*save_tmp, var);
        free(*save_tmp);
        *save_tmp = ft_strjoin(save, " ");
        free(save);
    }
    free(var);
}

char	*ft_change_input(char **str, t_env *env, t_data *data)
{
	char **tmp;
	char *save_tmp;
	int x;
    char *tmp_tmp_tmp;
	char *save;

	save_tmp =NULL;
	save = ft_strjoin((*str), " ");
	while (count_dollars_outside_quotes((*str))<=0)
		break;
    tmp_tmp_tmp = ft_change_input_v2(save);
	save_tmp = ft_strdup(" ");
	tmp = ft_split_d((save));
	free(save);
	x = -1;
	while(tmp[++x])
        ft_change_input_loop(tmp[x], env, data, &save_tmp);
	free((*str));
	free(tmp[x]);
	free(tmp);
	return(save_tmp);
}
