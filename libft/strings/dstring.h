/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:00 by tdelage           #+#    #+#             */
/*   Updated: 2024/09/02 14:27:23 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSTRING_H
# define DSTRING_H

# include "../libft.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

typedef enum e_string_error
{
	STRING_MALLOC_ERROR,
	STRING_NO_FREE_UNOWNED,
	STRING_NO_MODIFY_UNOWNED,
	STRING_CORRUPTED,
	STRING_EMPTY,
	STRING_NEEDLE_TOO_LONG,
	STRING_NEEDLE_NOT_FOUNDED,
	STRING_SUBSTR_OUT_OF_BOUND,
	STRING_CONVERSION_OVERFLOW,
	STRING_NOT_CONVERTIBLE,
	STRING_NULL_FUNCTION,
	STRING_SUCCESS,
}					t_string_error;

enum e_string_error	string_error(bool set, enum e_string_error value);

typedef struct s_string
{
	char			*ptr;
	size_t			len;
	size_t			capacity;
	bool			unowned;
}					t_string;

typedef bool		(*t_string_obey_f)(char);

struct s_string		string_zero(void);

struct s_string		string_new_from_cstr(char *s);
struct s_string		string_new(char *s, size_t len);
struct s_string		string_new_with_capacity(size_t capa);
struct s_string		string_new_u_from_cstr(char *s);
struct s_string		string_new_u(char *s, size_t len);

void				string_destroy(struct s_string *s);

struct s_string		string_copy(struct s_string self);

void				string_erase(struct s_string *self, size_t start,
						size_t len);
void				string_append(struct s_string *self, struct s_string str);
void				string_insert(struct s_string *self, struct s_string str,
						size_t start);
void				string_push(struct s_string *self, char c);
char				string_pop(struct s_string *self);
void				string_push_front(struct s_string *self, char c);
char				string_pop_front(struct s_string *self);
struct s_string		*string_split(struct s_string hay, struct s_string needle,
						size_t *count);
size_t				string_search(struct s_string hay, struct s_string needle);
void				string_trim(struct s_string *self, struct s_string chars);
struct s_string		string_substr(struct s_string self, size_t start,
						size_t end);
bool				string_contain(char c, struct s_string chars);
bool				string_equal(struct s_string s1, struct s_string s2);
void				string_count(struct s_string self, char c, size_t *of,
						size_t *ofnt);
size_t				string_count_ofnt(struct s_string self, char c);
size_t				string_count_of(struct s_string self, char c);
bool				string_obey(struct s_string self, t_string_obey_f func);

int8_t				string_to_sbyte(struct s_string self);
uint8_t				string_to_ubyte(struct s_string self);
int16_t				string_to_sword(struct s_string self);
uint16_t			string_to_uword(struct s_string self);
int32_t				string_to_sdword(struct s_string self);
uint32_t			string_to_udword(struct s_string self);
int64_t				string_to_sqword(struct s_string self);
uint64_t			string_to_uqword(struct s_string self);
bool				string_to_bool(struct s_string self);
float				string_to_float(struct s_string self);
char				*string_to_cstr(struct s_string self);
// double				string_to_double(struct s_string self);
// long double			string_to_long_double(struct s_string self);

struct s_string		string_from_sbyte(int8_t value);
struct s_string		string_from_ubyte(uint8_t value);
struct s_string		string_from_sword(int16_t value);
struct s_string		string_from_uword(uint16_t value);
struct s_string		string_from_sdword(int32_t value);
struct s_string		string_from_udword(uint32_t value);
struct s_string		string_from_sqword(int64_t value);
struct s_string		string_from_uqword(uint64_t value);
struct s_string		string_from_bool(bool value);
struct s_string		string_from_float(float value, int a_dot);
// struct s_string		string_from_double(double value);
// struct s_string		string_from_long_double(long double value);

#endif // DARRAY_H
