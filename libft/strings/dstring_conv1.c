#include "dstring.h"
#include "dstring_utils.h"

uint64_t	string_to_uqword_ovf(struct s_string self, uint64_t ovf)
{
	uint64_t	ret;
	size_t		i;
	size_t		last;

	ret = 0;
	i = 0;
	last = 0;
	while (i < self.len && ft_isdigit(self.ptr[i]) && ret >= last)
	{
		last = ret;
		ret *= 10;
		ret += self.ptr[i] - '0';
		if (ovf > 0)
			ret %= ovf;
		i++;
	}
	if (ret < last)
		string_error(true, STRING_CONVERSION_OVERFLOW);
	return (ret);
}

size_t	string_conv_trimspaces(struct s_string self)
{
	size_t	off;

	off = 0;
	while (off < self.len && ft_isspace(self.ptr[off]))
		off++;
	return (off);
}

bool	string_is_negative(struct s_string self, size_t *off)
{
	bool	negative;

	negative = false;
	if (self.ptr[*off] == '-')
		negative = true;
	if (self.ptr[*off] == '-' || self.ptr[*off] == '+')
		(*off)++;
	return (negative);
}

int8_t	string_to_sbyte(struct s_string self)
{
	size_t	off;
	bool	negative;
	uint8_t	ret;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	negative = string_is_negative(self, &off);
	ret = string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off),
			256);
	if (string_error(false, 0) == STRING_CONVERSION_OVERFLOW)
		return (ret);
	if (ret > MAX_I8 + negative)
	{
		string_error(true, STRING_CONVERSION_OVERFLOW);
		return (ret);
	}
	if (negative)
		return (-ret);
	else
		return (ret);
}

uint8_t	string_to_ubyte(struct s_string self)
{
	size_t	off;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	return (string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off),
			256));
}
