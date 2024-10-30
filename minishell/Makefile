# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 17:09:10 by dpoltura          #+#    #+#              #
#    Updated: 2024/10/30 14:59:05 by aduriez          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -g -fPIE -Wno-unused-command-line-argument
LDFLAGS = -lreadline #-fsanitize=address
CC = cc
SRCS =	minishell_parse.c \
		minishell_parse2.c \
		minishell_parse3.c \
		minishell_parse4.c \
		minishell_parse5.c \
		shell_loop.c \
		shell_loop2.c \
		ft_verif_input.c \
		ft_verif_tokens.c \
		ft_change_input.c \
		ft_exit.c \
		ft_parsing.c \
		ft_parsing2.c \
		ft_parsing3.c \
		ft_parsing4.c \
		ft_utils_pars9.c \
		ft_utils_pars8.c \
		ft_utils_pars7.c \
		ft_utils_pars6.c \
		ft_utils_pars5.c \
		ft_utils_pars4.c \
		ft_utils_pars3.c \
		ft_utils_pars2.c \
		ft_utils_pars.c \
		ft_insert_with_quote.c \
		ft_init.c \
		ft_verif.c \
		lexer5.c \
		lexer4.c \
		lexer3.c \
		lexer2.c \
		lexer.c \
		ft_here_doc.c \
		ft_here_doc2.c \
		ft_here_doc3.c \
		ft_here_doc4.c \
		ft_split.c \
		ft_exceve12.c \
		ft_exceve11.c \
		ft_exceve10.c \
		ft_exceve9.c \
		ft_exceve8.c \
		ft_exceve7.c \
		ft_exceve6.c \
		ft_exceve5.c \
		ft_exceve4.c \
		ft_exceve3.c \
		ft_exceve2.c \
		ft_exceve.c \
		ft_free.c \
		ft_bulting.c \
		ft_bulting_pwd.c \
		ft_bulting_cd2.c \
		ft_bulting_cd.c \
		ft_bulting_echo.c \
		ft_bulting_exit.c \
		ft_bulting_export3.c \
		ft_bulting_export2.c \
		ft_bulting_export.c \
		ft_bulting_unset.c \
		ft_bulting_env.c \
		ft_insert_new_tab.c \
		ft_insert_new_tab2.c \

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
