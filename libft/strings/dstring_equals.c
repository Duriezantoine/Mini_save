#include "dstring.h"
#include "dstring_utils.h"

bool	string_equal(struct s_string s1, struct s_string s2)
{
	if (!string_check(s1) || !string_check(s2))
		return (false);
	if (s1.len != s2.len)
		return (false);
	return (ft_strncmp(s1.ptr, s2.ptr, s1.len) == 0);
}

void	string_count(struct s_string self, char c, size_t *of, size_t *ofnt)
{
	size_t	i;
	size_t	tmp;

	if (!string_check(self))
		return ;
	if (of == NULL)
		of = &tmp;
	if (ofnt == NULL)
		ofnt = &tmp;
	*of = 0;
	*ofnt = 0;
	i = 0;
	while (i < self.len)
	{
		if (self.ptr[i] == c)
			(*of)++;
		else
			(*ofnt)++;
		i++;
	}
}

size_t	string_count_of(struct s_string self, char c)
{
	size_t	of;

	string_count(self, c, &of, NULL);
	return (of);
}

size_t	string_count_ofnt(struct s_string self, char c)
{
	size_t	of;

	string_count(self, c, NULL, &of);
	return (of);
}

bool	string_obey(struct s_string self, t_string_obey_f func)
{
	size_t	i;

	if (!string_check(self))
		return (false);
	if (func == NULL)
	{
		string_error(true, STRING_NULL_FUNCTION);
		return (false);
	}
	i = 0;
	while (i < self.len)
	{
		if (!func(self.ptr[i]))
			return (false);
		i++;
	}
	return (true);
}
