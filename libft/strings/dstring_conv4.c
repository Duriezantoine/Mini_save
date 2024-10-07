#include "dstring.h"

struct s_string	string_from_sbyte(int8_t value)
{
	struct s_string	ret;
	bool			negative;

	if (value == 0)
		return (string_copy(string_new_u_from_cstr("0")));
	negative = value < 0;
	if (negative)
		ret = string_from_ubyte(-value);
	else
		return (string_from_ubyte(value));
	if (negative && string_error(false, 0) == STRING_SUCCESS)
		string_push_front(&ret, '-');
	return (ret);
}

struct s_string	string_from_ubyte(uint8_t value)
{
	struct s_string	ret;

	if (value == 0)
		return (string_copy(string_new_u_from_cstr("0")));
	ret = string_new_with_capacity(1);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (ret);
	while (value && string_error(false, 0) == STRING_SUCCESS)
	{
		string_push_front(&ret, value % 10 + '0');
		value /= 10;
	}
	return (ret);
}

struct s_string	string_from_sword(int16_t value)
{
	struct s_string	ret;
	bool			negative;

	if (value == 0)
		return (string_copy(string_new_u_from_cstr("0")));
	negative = value < 0;
	if (negative)
		ret = string_from_uword(-value);
	else
		return (string_from_uword(value));
	if (negative && string_error(false, 0) == STRING_SUCCESS)
		string_push_front(&ret, '-');
	return (ret);
}

struct s_string	string_from_uword(uint16_t value)
{
	struct s_string	ret;

	if (value == 0)
		return (string_copy(string_new_u_from_cstr("0")));
	ret = string_new_with_capacity(1);
	if (string_error(false, 0) != STRING_SUCCESS)
		return (ret);
	while (value && string_error(false, 0) == STRING_SUCCESS)
	{
		string_push_front(&ret, value % 10 + '0');
		value /= 10;
	}
	return (ret);
}
