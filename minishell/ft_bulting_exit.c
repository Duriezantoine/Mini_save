/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:05:36 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/20 17:41:07 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>


size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	counter;

	count = ft_strlen((char *)src);
	counter = 0;
	if (size != 0)
	{
		while (src[counter] != '\0' && counter < size - 1)
		{
			dst[counter] = src[counter];
			counter++;
		}
		dst[counter] = '\0';
	}
	return (count);
}

char	*ft_substr(char  *s, unsigned int start, size_t  len)
{
	char			*subst;
	size_t			size;
	unsigned int	j;

	j = 0;
	if (!s)
		return (NULL);
	j = ft_strlen(s);
	if (start >= j)
	{
		subst = ft_strdup("");
		return (subst);
	}
	size = ft_strlen(s + start);
	if (size < len)
		len = size;
	subst = (char *)malloc(sizeof(char) * (len + 1));
	if (!subst)
		return (NULL);
	ft_strlcpy(subst, s + start, len + 1);
	return (subst);
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((unsigned char *)dest + i) = *((unsigned char *)src + i);
		i++;
	}
	return (dest);
}

static char	*ft_trim_space(const char *str)
{
	size_t	i;

	i = 0;
	while (ft_white_space(str[i]))
		i++;
	return ((char *)str + i);
}

static int	ft_from_buff_to_i(char *tmp, int st_index, int sign)
{
	size_t	pow;
	size_t	ret;

	pow = 1;
	ret = 0;
	while (st_index-- > 0)
	{
		ret += (tmp[st_index] - '0') * pow;
		pow *= 10;
	}
	return (ret * sign);
}

int	ft_atoi(const char *str)
{
	char	tmp[32];
	int		sign;
	size_t	t;

	str = ft_trim_space(str);
	sign = 1;
	t = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		sign = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && t < 32)
	{
		tmp[t] = *str;
		t++;
		str++;
	}
	return (ft_from_buff_to_i(tmp, t, sign));
}

static int	is_separator(char c, const char *set)
{
	int	count_set;

	count_set = 0;
	while (set[count_set])
	{
		if (set[count_set] == c)
			return (1);
		count_set++;
	}
	return (0);
}

int     ft_check_space(char *str)
{
    int i;
    i = 0;
    while(str[i])
    {
        if (!ft_white_space(str[i]))
            return(1);
        i++;
    }
    return(0);
}

char	*ft_strtrim(char *s1, char *set)
{
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1)
		return (NULL);
    // if(ft_check_space(s1) == 0)
    //     return(NULL);
    if (!set)
		return (ft_strdup(s1));
	while (is_separator(*s1, set) == 1)
	{
		s1++;
		i++;
	}
	len = ft_strlen(s1) - 1;
	while (is_separator(s1[len], set) == 1)
		len--;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	return (ft_substr(s1, 0, (unsigned int) len + 1));
} 

int ft_verif_number(char *str)
{
    char *start = str;
    char *end;
    int has_digits = 0;

    // Ignorer les espaces au début
    while (*str && isspace(*str))
        str++;

    // Vérifier le signe
    if (*str == '+' || *str == '-')
        str++;

    // Vérifier les chiffres
    while (*str)
    {
        if (isdigit(*str))
            has_digits = 1;
        else if (!isspace(*str))
            return 1;  // Caractère non valide trouvé
        str++;
    }

    // Vérifier s'il y a des chiffres et retirer les espaces à la fin
    end = str - 1;
    while (end > start && isspace(*end))
        end--;

    // Si la chaîne est vide ou ne contient que des espaces
    if (start == str && !has_digits)
        return 2;

    // Si la chaîne ne contient pas de chiffres
    if (!has_digits)
        return 1;

    return 0;  // Nombre valide
}

long	ft_strtol(char *str, char **endptr)
{
	long	res;
	short	sign;

	if (!str || *str == '\0')
		return (0);
	while ((*str >= 8 && *str <= 12) || *str == ' ')
		str++;
	sign = 1;
	res = 0;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
	{
		if ((sign == 1 &&  res > (LONG_MAX - (*str - '0')) / 10)
			|| (sign == -1 && -res < (LONG_MIN + (*str - '0')) / 10))
			break;
		else
			res = res * 10 + (*str - '0');
		str++;
	}
	*endptr = str;
	return (res * sign);
}

int bulting_exit(char **args, t_node *list, t_env **env, t_data *data)
{
    (void) env;
    (void) list;
    long exit_status;
    char *endptr;

    if (args[1] == NULL)
		return (data->exit_code);

	exit_status = ft_strtol(args[1], &endptr);
	
	if (*endptr != '\0' || endptr == args[1]) 
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return 2;
	}

	if (args[2] != NULL)
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return 1;
	}
	else
		return (exit_status & 255);
}