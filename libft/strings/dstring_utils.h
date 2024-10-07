/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstring_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 04:50:28 by tdelage           #+#    #+#             */
/*   Updated: 2024/08/01 17:54:57 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DSTRING_UTILS_H
# define DSTRING_UTILS_H

# include "dstring.h"

bool		string_check(struct s_string self);
bool		string_grow(struct s_string *self);
char		*calculate_trim(struct s_string self, struct s_string chars);
size_t		calculate_trim_len(struct s_string self, struct s_string chars);
uint64_t	string_to_uqword_ovf(struct s_string self, uint64_t ovf);
size_t		string_conv_trimspaces(struct s_string self);
bool		string_is_negative(struct s_string self, size_t *off);

#endif // DSTRING_UTILS_H
