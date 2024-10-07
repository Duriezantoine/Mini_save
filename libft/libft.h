/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:11:06 by tdelage           #+#    #+#             */
/*   Updated: 2024/10/07 22:51:20 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_iodef.h"
# include "ft_structs.h"
# include "ft_types.h"
# include <stddef.h>

// ft_arena
struct s_arena		ft_arena_create(size_t size);
void				ft_arena_destroy(struct s_arena *arena);
void				*ft_arena_alloc(struct s_arena *arena, size_t size);

// ft_list
struct s_llist		ft_llist_create(void);
void				ft_llist_destroy(struct s_llist *list, t_lstdel_f del);
struct s_llist_node	*ft_llist_node_create(void *data);
void				ft_llist_node_destroy(struct s_llist_node *node,
						t_lstdel_f del);
void				ft_llist_append(struct s_llist *list,
						struct s_llist_node *node);
struct s_llist_node	*ft_llist_truncate(struct s_llist *list);
void				ft_llist_push(struct s_llist *list,
						struct s_llist_node *node);
struct s_llist_node	*ft_llist_pop(struct s_llist *list);
struct s_llist_node	*ft_llist_get(struct s_llist *list, t_u64 idx);

// ft_complex
struct s_complex	ft_complex_create(t_f64 real, t_f64 imag);
struct s_complex	ft_complex_add(struct s_complex a, struct s_complex b);
struct s_complex	ft_complex_sub(struct s_complex a, struct s_complex b);
struct s_complex	ft_complex_mul(struct s_complex a, struct s_complex b);
struct s_complex	ft_complex_div(struct s_complex a, struct s_complex b);

// ft_memory
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_realloc(char *ptr, size_t last, size_t n);
void				ft_free(const char *free_pattern, ...);
void				ft_free_register(char c, t_free_function f);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

// ft_chars
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isspace(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

// ft_cstrings
size_t				ft_strlen(const char *s);
size_t				ft_strlenc(const char *s, char c);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t size);
char				*ft_strnstr(const char *str, const char *sub, size_t n);
char				*ft_strdup(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_strsufix(char *s, char *sufix);
int					ft_strprefix(char *s, char *prefix);
char				**ft_split(char const *str, char charset);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

// ft_convert
char				*ft_itoa(int n);
int					ft_atoi(const char *str);

// ft_output
int					ft_putchar_fd(char c, int fd);
int					ft_putstr_fd(char *str, int fd);
int					ft_putendl_fd(char *str, int fd);
int					ft_putnbr_fd(long long int nb, int fd, int radix, int up);
int					ft_putunbr_fd(unsigned long long int nb, int fd, int radix,
						int up);

// ft_rand
void				ft_srand(unsigned int seed);
int					ft_rand(int a, int b);

// ft_count
void				ft_count(char *str, char c, size_t *of, size_t *ofnt);
size_t				ft_countof(char *str, char c);
size_t				ft_countofnot(char *str, char c);

#endif // LIBFT_H
