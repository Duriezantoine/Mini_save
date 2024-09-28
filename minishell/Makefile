# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 17:09:10 by dpoltura          #+#    #+#              #
#    Updated: 2024/09/28 10:50:00 by aduriez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g -fPIE -Wno-unused-command-line-argument
LDFLAGS = -lreadline

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

OBJS = $(SRCS:%.c=%.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all
