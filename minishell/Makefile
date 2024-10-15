# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 17:09:10 by dpoltura          #+#    #+#              #
#    Updated: 2024/10/15 08:48:19 by aduriez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g -fPIE -Wno-unused-command-line-argument
LDFLAGS = -lreadline #-fsanitize=address

SRCS =	minishell_parse.c \
		ft_exit.c \
		ft_parsing.c \
		ft_utils_pars.c \
		ft_init.c \
		ft_verif.c \
		lexer.c \
		ft_here_doc.c \
		ft_signaux.c \
		ft_init_env.c \
		ft_split.c \
		ft_exceve.c \
		ft_free.c \
		ft_bulting.c \
		ft_bulting_pwd.c \
		ft_bulting_cd.c \
		ft_bulting_echo.c \
		ft_bulting_export.c \
		ft_bulting_unset.c \
		ft_bulting_env.c \
		ft_insert_new_tab.c \

OBJS = $(SRCS:%.c=%.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	rm -fr $(OBJS)

fclean: clean
	rm -fr $(NAME)

re: fclean all
