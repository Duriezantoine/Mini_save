#include "dstring.h"
#include "dstring_utils.h"

int64_t	string_to_sqword(struct s_string self)
{
	size_t		off;
	bool		negative;
	uint64_t	ret;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	negative = string_is_negative(self, &off);
	ret = string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off), 0);
	if (string_error(false, 0) == STRING_CONVERSION_OVERFLOW)
		return (ret);
	if (ret > (size_t)MAX_I64 + negative)
	{
		string_error(true, STRING_CONVERSION_OVERFLOW);
		return (ret);
	}
	if (negative)
		return (-ret);
	else
		return (ret);
}

uint64_t	string_to_uqword(struct s_string self)
{
	size_t	off;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	return (string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off),
			0));
}

bool	string_to_bool(struct s_string self)
{
	size_t	off;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	if (self.len - off >= 4 && ft_strncmp(self.ptr + off, "true", 4) == 0)
		return (true);
	if (self.len - off >= 5 && ft_strncmp(self.ptr + off, "false", 4) == 0)
		return (false);
	string_error(true, STRING_NOT_CONVERTIBLE);
	return (false);
}
