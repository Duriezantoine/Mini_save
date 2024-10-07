#include "dstring.h"
#include "dstring_utils.h"

int16_t	string_to_sword(struct s_string self)
{
	size_t		off;
	bool		negative;
	uint16_t	ret;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	negative = string_is_negative(self, &off);
	ret = string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off),
			MAX_U16 + 1);
	if (string_error(false, 0) == STRING_CONVERSION_OVERFLOW)
		return (ret);
	if (ret > MAX_I16 + negative)
	{
		string_error(true, STRING_CONVERSION_OVERFLOW);
		return (ret);
	}
	if (negative)
		return (-ret);
	else
		return (ret);
}

uint16_t	string_to_uword(struct s_string self)
{
	size_t	off;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	return (string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off),
			MAX_U16 + 1));
}

int32_t	string_to_sdword(struct s_string self)
{
	size_t		off;
	bool		negative;
	uint32_t	ret;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	negative = string_is_negative(self, &off);
	ret = string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off),
			MAX_U32 + 1);
	if (string_error(false, 0) == STRING_CONVERSION_OVERFLOW)
		return (ret);
	if (ret > (size_t)MAX_I32 + negative)
	{
		string_error(true, STRING_CONVERSION_OVERFLOW);
		return (ret);
	}
	if (negative)
		return (-ret);
	else
		return (ret);
}

uint32_t	string_to_udword(struct s_string self)
{
	size_t	off;

	if (!string_check(self))
		return (0);
	off = string_conv_trimspaces(self);
	return (string_to_uqword_ovf(string_new_u(self.ptr + off, self.len - off),
			MAX_U32 + 1));
}
