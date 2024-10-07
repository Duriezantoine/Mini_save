#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include "dstring.h"
#include "dstring_utils.h"

static struct s_string	destroy_zero(struct s_string *a)
{
	if (a)
		string_destroy(a);
	return (string_zero());
}

void	add_start_zero(struct s_string *ret, float fpart, int p)
{
	string_push(ret, '.');
	while (fpart < (int)(p / 10) && string_error(false, 0) == STRING_SUCCESS)
	{
		fpart *= 10;
		string_push(ret, '0');
	}
}

struct s_string	string_from_float(float value, int a_dot)
{
	struct s_string	ret;
	float			fpart;
	struct s_string	dec;

	ret = string_from_sqword((int64_t)value);
	if (string_error(false, 0) != STRING_SUCCESS)
		return ((struct s_string){0});
	fpart = (value - (int64_t)value) * pow(10, a_dot);
	fpart *= -1 + 2 * (!(value < 0 && (int)value == 0));
	if ((size_t)fpart == 0)
		return (ret);
	add_start_zero(&ret, fpart, pow(10, a_dot));
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_zero(&ret));
	dec = string_from_uqword(fpart);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_zero(&ret));
	string_append(&ret, dec);
	string_destroy(&dec);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (destroy_zero(&ret));
	if (value < 0 && (int)value == 0)
		string_push_front(&ret, '-');
	return (ret);
}

char	*string_to_cstr(struct s_string self)
{
	char	*ret;

	if (!string_check(self) || self.len == 0)
		return (NULL);
	ret = ft_calloc(self.len + 1, sizeof(char));
	if (!ret)
	{
		string_error(true, STRING_MALLOC_ERROR);
		return (NULL);
	}
	ft_memcpy(ret, self.ptr, self.len);
	return (ret);
}
