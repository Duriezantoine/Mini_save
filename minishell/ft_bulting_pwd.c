/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:51:36 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/25 14:22:27 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bulting_pwd(void)
{
	char	str[1200];

	if (getcwd(str, sizeof(str)) != NULL)
		printf("%s\n", str);
}
