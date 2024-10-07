#include "dstring.h"

struct s_string	string_from_sdword(int32_t value)
{
	struct s_string	ret;
	bool			negative;

	if (value == 0)
		return (string_copy(string_new_u_from_cstr("0")));
	negative = value < 0;
	if (negative)
		ret = string_from_udword(-value);
	else
		return (string_from_udword(value));
	if (negative && string_error(false, 0) == STRING_SUCCESS)
		string_push_front(&ret, '-');
	return (ret);
}

struct s_string	string_from_udword(uint32_t value)
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

struct s_string	string_from_sqword(int64_t value)
{
	struct s_string	ret;
	bool			negative;

	if (value == 0)
		return (string_copy(string_new_u_from_cstr("0")));
	negative = value < 0;
	if (negative)
		ret = string_from_uqword(-value);
	else
		ret = string_from_uqword(value);
	if (negative && string_error(false, 0) == STRING_SUCCESS)
		string_push_front(&ret, '-');
	return (ret);
}

struct s_string	string_from_uqword(uint64_t value)
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

struct s_string	string_from_bool(bool value)
{
	if (value)
		return (string_copy(string_new_u_from_cstr("true")));
	return (string_copy(string_new_u_from_cstr("false")));
}
