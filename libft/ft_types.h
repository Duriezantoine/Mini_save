/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:23:05 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/04 22:06:06 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H

# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

# define MAX_U8 0xFF
# define MAX_U16 0xFFFF
# define MAX_U32 0xFFFFFFFF
# define MAX_U64 0xFFFFFFFFFFFFFFFF

# define MAX_I8 0x7F
# define MAX_I16 0x7FFF
# define MAX_I32 0x7FFFFFFF
# define MAX_I64 0x7FFFFFFFFFFFFFFF

# define MIN_I8 0x80
# define MIN_I16 0x8000
# define MIN_I32 0x80000000
# define MIN_I64 0x8000000000000000

# define MAX_F32 3.402823e+38
# define MAX_F64 1.797693e+308
# define MAX_F128 1.189731e+4932L

# define MIN_F32 1.175494e-38
# define MIN_F64 2.225074e-308
# define MIN_F128 3.362103e-4932L

typedef unsigned char		t_u8;
typedef unsigned short		t_u16;
typedef unsigned int		t_u32;
typedef unsigned long long	t_u64;

typedef signed char			t_i8;
typedef signed short		t_i16;
typedef signed int			t_i32;
typedef signed long long	t_i64;

typedef float				t_f32;
typedef double				t_f64;
typedef long double			t_f128;

typedef t_u8				t_bool;

typedef int					t_fd;

typedef void				(*t_lstdel_f)(void *);
typedef void				(*t_free_function)(void *);

#endif // TYPES_H
