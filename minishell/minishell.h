/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:05:05 by dpoltura          #+#    #+#             */
/*   Updated: 2024/09/28 12:43:28 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSE_H
#define MINISHELL_PARSE_H

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

typedef enum e_tokens
{
	INFILE,
	OUTFILE,
	INPUT,
	HEREDOC,
	DELIM,
	OUTPUT,
	APPEND,
	PIPE,
	CMD,
	ARG,
	OPTION,
	REDIR,
	OUTPUT_ADD
} t_token;


typedef struct s_env
{
	char			*key;
	char			**value;
	struct s_env	*next;

}					t_env;


typedef struct s_arg
{
	char *str_command;
	int type;

	struct s_arg *prev;
	struct s_arg *next;
} t_arg;

typedef struct s_cmd
{
	char **cmd_and_args;

	int input;
	int output;

	int is_builtin;

	struct s_cmd *next;
	struct s_cmd *prev;
} t_cmd;

typedef struct s_node
{
	struct s_arg *arg;
	struct s_cmd *cmd;
	struct s_env *env;

	int save[2];
	int pipe[2];

	struct s_node *prev;
    struct s_node *next;

	
} t_node;

//Pour le parsing

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
int shell_loop(t_node *list, t_data **data, t_env **env);
void organisation_shell_loop(t_node *list, t_data **data);
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
void ft_init_tab_echo_malloc(t_echo *data_echo, char *input, int i);

int ft_nbr_quot(char *input, int i);
void ft_parsing_init(t_command **command, t_data *data, char *input);
int ft_parsing(t_node *list, t_data **data, char *input);
char **split_string(char *str, int *len);
void ft_init_data(t_data **data, t_node *list);
int ft_init_token_space(t_echo *data_echo, char *input, int i);
void ft_init_echo_malloc(t_echo *data_echo);
void ft_insert_data_w_quot(t_echo *data_echo, char *input, int *i, int *place_tab_w_quot);
void ft_insert_data_s_quot(t_echo *data_echo, char *input, int *i, int *place_tab_s_quot);
void ft_insert_data_s_whith_tab(t_echo *data_echo, char *input, int *i, int *clef_tab_s_quot);
void ft_insert_data_w_whith_tab(t_echo *data_echo, char *input, int *i, int *clef_tab_w_quot);
void ft_insert_new_data_with_data(char **save, t_echo *data_echo);
void ft_insert_list(t_node **list, t_echo **data_echo);
void ft_search_built(t_node **list, char **save);
t_arg *ft_init_list(t_node *list, t_echo *data_echo, char *save);
int ft_split_with_space(t_echo *data_echo, char *input);

void print_list(t_node *list);
int ft_strcmp(char *s1, char *s2);
void type_insert_cmd(t_arg *new_node);
void ft_format_list(t_arg *arg);
void ft_insert_tab_echo(t_echo *data_echo, char *input, int i);
void ft_init_data_list(t_node **list);
void   lexer_cmd(t_node *list, t_data *data);
void print_liste(t_arg *list);

void lexer(t_node *head);



//Fonction pour free

void free_t_echo(t_echo *echo);

//Fonction pour les signauxx 
void	ft_manager_sig(int sig);
void	ft_init_signaux(struct sigaction *action, char **write_here_do);

//Fonction pour le here_doc

void	ft_here_doc(t_data *data, t_node *list , t_env **env, char *limiteur);
//Fonction pour l'environnement
void	ft_init_env(t_env **env);
char	**ft_split(char const *s, char c);


#endif
