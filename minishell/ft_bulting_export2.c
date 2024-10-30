/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_export2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:15:32 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/28 13:24:31 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_copy_start(char *str, char c)
{
	int		x;
	char	*dest;
	int		i;

	i = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == c)
			break ;
		x++;
	}
	dest = malloc(sizeof(char *) * (x + 1));
	while (i < x)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_verif_export_add_equal(char *str)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] == '+')
			if (str[x + 1] != '=')
				return (0);
		x++;
	}
	return (1);
}

int	ft_verif_key_letter_number_underscore(char *str)
{
	int		x;
	char	*end;
	char	*sep;

	x = 0;
	sep = ft_strchr(str, '+');
	if (sep == NULL)
		end = ft_copy_start(str, '=');
	else
		end = ft_copy_start(str, '+');
	if (end[0] == '\0')
		return (1);
	while (end[x])
	{
		if ((str[x] < 48 || str[x] > 57) && (str[x] < 65 || str[x] > 90)
			&& (str[x] < 97 || str[x] > 122) && str[x] != 95)
			return (1);
		x++;
	}
	return (0);
}

int	ft_verif_one_letter(char *str)
{
	if (str == NULL || *str == '\0')
		return (1);
	if (str[0] >= '0' && str[0] <= '9')
	{
		write(2, "export: `", 9);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	return (0);
}

int	ft_verif_export(char *str)
{
	if (ft_verif_export_add_equal(str) == 0)
	{
		write(2, "export: not valid in this context: ", 30);
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
		return (1);
	}
	if (ft_verif_key_letter_number_underscore(str) == 1)
	{
		write(2, "export: `", 9);
		write(2, str, ft_strlen(str));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	if (ft_verif_one_letter(str) == 1)
	{
		printf("La");
		return (1);
	}
	return (0);
}
