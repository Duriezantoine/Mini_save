/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:05:05 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/28 17:07:21 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
#define MINISHELL_PARSE_H

#include "colors.h"
#include <dirent.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

typedef struct s__node
{
	int infile;
	int outfile;
	struct Node *next;
} t_node;

typedef struct s_env
{
	char *key;
	char **value;
	struct s_env *next;
} t_env;

typedef struct s_token_str_two
{
	// Chaque command est separer par une pipe
	char *str;
	char *token;

} t_token_str_two;

typedef struct s_command
{
	// Chaque command est separer par une pipe
	char *input_split;
	t_token_str_two *name;
	int b;

} t_command;

typedef struct s_data
{
	int nbr_command;

} t_data;

typedef struct s_str
{
	char *str;
	int order;
} t_str;

typedef struct s_echo
{
	int s_quot;
	int w_quot;
	t_str *str_w_quot;
	t_str *str_s_quot;
	int order_occurence;
} t_echo;

int main(int argc, char **argv, char **envp);
void shell_loop(t_node ***list, t_data **data, char **env);
void organisation_shell_loop(t_node ***list, t_data **data, char **env);
void ft_insert_cmd(t_command **command, t_data **data, char *input);
void free_tokens(char **tokens, int len);
void ft_insert_token(t_command **command, t_data **data);
void ft_verif_token(t_command **command, t_data **data);

// Exits
int ft_putstr_fd(char *str, int fd);
void ft_out_exit(int i);

// Utils
void *ft_memset(void *s, int c, size_t n);
int ft_strlen(char *str);
char *ft_strjoin(char const *s1, char const *s2);
void *ft_calloc(size_t elementCount, size_t elementSize);
void *ft_bzero(void *s, size_t n);
char *ft_strdup(char *src);
int ft_isalnum(int c);

// Parsing
int ft_nbr_quot(char *input, int i);
void ft_parsing_init(t_command **command, t_data *data, char *input);
void ft_parsing(t_node ***list, t_data **data, char *input);
char **split_string(char *str, int *len);
void ft_init_data(t_data **data);
void ft_init_token_space(t_echo **data_echo, char *input, int i);
void ft_init_echo_malloc(t_echo **data_echo);
void ft_init_tab_echo_malloc(t_echo **data_echo, char *input, int i);
void ft_insert_data_w_quot(t_echo **data_echo, char *input, int *i, int *place_tab_w_quot);
void ft_insert_data_s_quot(t_echo **data_echo, char *input, int *i, int *place_tab_s_quot);
void ft_insert_tab_echo(t_echo **data_echo, char *input, int i);
void ft_insert_data_s_whith_tab(t_echo **data_echo, char *input, int *i, int *clef_tab_s_quot);
void ft_insert_data_w_whith_tab(t_echo **data_echo, char *input, int *i, int *clef_tab_w_quot);

#endif
