/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bulting_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:05:36 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/15 18:26:57 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
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
        if (str[i] != ' ')
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
int  ft_verif_number(char *str)
{
    int i;
    i= 0;
    char *tmp;

    tmp = ft_strtrim(str, " "); // str == "       " -> ""ft
    printf("Je ssuis tmp|%s|", tmp);
    if (tmp[0] == '\0')
    {   
        tmp = ft_strdup("la");
        printf("La chaîne est vide\n");//C'est ici demande ce que l'on renvoit
        free(tmp);
        return 2;
    }
    
    // printf("aa: %s\n", tmp);
    if (tmp[0] == 0)
    {
        free(tmp);
        return (1);
    }
    while(tmp[i])
    {
        if(tmp[i] < '0' || tmp[i] > '9')
        {
            free(tmp);
            return(1);
        }
        i++;
    }
    free(tmp);
    return(0);
}

int bulting_exit(char **args, t_node *list, t_env **env)
{
    (void) env;
    (void) list;
    if(args[1]== NULL)
        return(0); // todo get last exit code
    if(ft_verif_number(args[1]) == 0)
    {
        if (args[2] != NULL)
        {
            ft_putstr_fd("bash: exit: too many arguments", 2);
            return (-1);
        }
        else
            return (ft_atoi(args[1]));
    }
    else
    {
        write(2, "bash: exit: ", 12);
        write(2, args[1], ft_strlen(args[1]));
        write(2, ": numeric argument required\n", 28);
        return (2);
    }
}