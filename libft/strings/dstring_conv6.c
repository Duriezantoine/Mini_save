#include "dstring.h"
#include "dstring_utils.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

static void	reset_neg(int *neg)
{
	*neg *= -1;
	if (*neg == 0)
		*neg = 1;
}

static void	set_neg(int *neg, char c)
{
	*neg = 0;
	if (c == '-')
		*neg = 1;
}

int	num_zero_a_dot(struct s_string self, int off)
{
	int	i;

	i = 0;
	while (self.ptr[off + i] == '0' && self.len > (size_t)off + i)
		i++;
	return (i);
}

float	string_to_float(struct s_string self)
{
	int64_t	dec;
	size_t	off;
	size_t	dec2;
	int		p;
	int		neg;

	if (!string_check(self) || self.len == 0)
		return (0);
	set_neg(&neg, self.ptr[0]);
	dec = string_to_sqword(string_new_u(self.ptr + neg, self.len));
	reset_neg(&neg);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (dec * neg);
	off = string_search(self, string_new_u_from_cstr(".")) + 1;
	if (string_error(false, 0) == STRING_NEEDLE_NOT_FOUNDED)
	{
		string_error(true, STRING_SUCCESS);
		return (dec * neg);
	}
	dec2 = string_to_uqword(string_new_u(self.ptr + off, self.len - off));
	p = log10((dec2 * 1.0)) + 1;
	if (dec2 == 0.f)
		p = 1;
	p += num_zero_a_dot(self, off);
	return ((dec * 1.0f + (dec2 / pow(10, p))) * neg);
}
