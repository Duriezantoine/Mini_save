/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:05:05 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/10 09:45:47 by aduriez          ###   ########.fr       */
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
	OUTPUT_ADD,
	HEREDOC_INFILE,
} t_token;
typedef struct
{
	char *write_here_do;
	int ret;
	int test;
	struct sigaction action;
	struct termios term_attr;
	char *temp_file_name;
	int tmp_fd;
} t_here_doc_data;

/// Strucuture pour l'environnement  ////////////////
typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;

} t_env;

typedef struct s_arg
{
	char *str_command;
	int type;
	int quot;
	struct s_arg *prev;
	struct s_arg *next;
} t_arg;

typedef struct s_cmd
{
	char **cmd_and_args;

	int input;
	int output;

	int cmd;
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

// Pour le parsing

typedef struct s_token_str_two
{
	// Chaque command est separer par une pipe
	char *str;
	char *token;

} t_token_str_two;

typedef struct s_save
{
	char *str;
	int bool;
	struct s_save *next;

} t_save;

typedef struct s_command
{
	// Chaque command est separer par une pipe
	char **input_split;
	t_token_str_two *name;
	int b;

} t_command;

/////////////////////////////////////////Utils pour le parsing///////////////////////////////////////////////////////////////////////////////

typedef struct s_data
{
	int nbr_command;
	char count;
	int bool;

} t_data;

typedef struct s_str
{
	char *str;
	int order;
	int bool;
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
void organisation_shell_loop(t_node *list, t_data *data);
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
char **ft_parsing_init(t_data *data, char *input);
int ft_parsing(t_node *list, t_data **data, char *input);
char **split_string(char *str, int *len);
int ft_init_token_space(t_echo *data_echo, char *input, int i);
void ft_init_echo_malloc(t_echo *data_echo);
void ft_insert_data_w_quot(t_echo *data_echo, char *input, int *i, int *place_tab_w_quot);
void ft_insert_data_s_quot(t_echo *data_echo, char *input, int *i, int *place_tab_s_quot);
void ft_insert_data_s_whith_tab(t_echo *data_echo, char *input, int *i, int *clef_tab_s_quot);
void ft_insert_data_w_whith_tab(t_echo *data_echo, char *input, int *i, int *clef_tab_w_quot);
void ft_insert_list(t_node **list, t_echo **data_echo);
void ft_search_built(t_node **list, char **save);
int ft_split_with_space(t_echo *data_echo, char *input);
char *ft_strcpy(char *dest, char *src);
char *ft_strcat(char *dest, char src);
void ft_insert_new_data_with_data(t_save **save, t_echo *data_echo);
void ft_insert_data_data_echo_s(t_save **save, t_echo *data_echo, int iterateur_s);
void ft_init_data(t_data ***data, t_node *list);
void print_list(t_node *list);
int ft_strcmp(char *s1, char *s2);
void type_insert_cmd(t_arg *new_node);
void ft_format_list(t_arg *arg);
void ft_insert_tab_echo(t_echo *data_echo, char *input, int i);
void ft_init_data_list(t_node **list);
void lexer_cmd(t_node *list, t_data *data);
void print_liste(t_arg *list);
void ft_insert_double_tab(t_cmd **list, t_arg *list_arg);
t_arg *ft_init_list(t_node *list, t_echo *data_echo, t_save *save);
void lexer(t_node *head);



// Fonction pour free
void free_t_echo(t_echo *echo);

// Fonction pour les signauxx
void ft_manager_sig(int sig);
void ft_init_signaux(struct sigaction *action, char **write_here_do);

// Fonction pour le here_doc

char *ft_here_doc(t_data *data, t_node *list, char *limiteur);
// Fonction pour l'environnement
void ft_init_env(t_env **env);
char **ft_split(char const *s, char c);

// Ce qui permet de verifier ou j'en suis
void print_cmd(t_node *list);
void print_all_cmds(t_node *list);

void	ft_open_infile(t_node **list, char *infile);

//Ce qui permet de mettre en place l'execution 
int    ft_exceve(t_node *list, t_data *data, t_env **env);//Hesitation a mettre un double pointeur mais normarlement c'est l'exec rien ne doit etre modifier quand on va a l'interieur 
void ft_exceve_bulting(t_cmd *cmd, t_node *list, t_env ***env);

//Cee qui permet de free
void free_node(t_node *list, t_data *data);
void 	ft_free_data_echo(t_echo *data_echo);
void ft_free_arg(t_arg *tmp);
void ft_free_cmd(t_cmd *cmd);

///////////////////////////////////////Pour les bultings///////////////////////////////////////////////
////////////////////////////////Pour le bulting cd/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void    bulting_cd (t_cmd *cmd,t_node *list ,t_env **env);
void    ft_simple_cd(char *s, t_env **env);
void    ft_change_env(char *save, t_env ***env);
char    *new_path_cd(char *s, t_env **env);
void    ft_exceve_cd(t_cmd *cmd, t_env **env);
char 	*ft_execute_cd_home(t_env **env, int i);
int     ft_no_cd_(char *s);
char 	*save_pwd(t_env **env);

////////////////////////////////Pour le bulting echo/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    bulting_echo(t_cmd *cmd, int i);
int 	ft_search_n(t_cmd *cmd, int i);
/////////////////////////////////Pour le bulting pwd/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	bulting_pwd();
/////////////////////////////////Pour le bulting export//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    bulting_export(t_cmd *cmd, t_node *list, t_env **env);
int     ft_verif_export_equal(char *str);
void    ft_delim_envp( t_env **env, char *str);
void    ft_change_envp(t_env **env, char *key, char *value);
int     ft_search_key_envp(t_env *env, char *key);
void ft_insert_envp(t_env **env, char *key, char *value);
char    *ft_copy_end(char *str, char c);
char    *ft_copy_start(char *str, char c);
int ft_verif_export_space(char *str);
int     ft_verif_export(char *str);
int     ft_verif_export_equal(char *str);
int		 ft_verif_export_space(char *str);

/////////////////////////////////Pour le bulting unset//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    bulting_unset(t_cmd *cmd, t_node *list);
int   ft_search_envp(t_env **env, char *search);
void   ft_delete_unset(t_env *env, char *search);
/////////////////////////////////Pour le bulting env//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bulting_env(t_cmd *cmd, t_node *list);
void sort_envp(t_env **env);
t_env *copy_env(t_env *env) ;
/////////////////////////////////Pour le free//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ft_free_end(t_node *list, t_env **env);
void 	ft_free_return_loop(t_node *list, t_data *data);

void ft_insert_nodes(t_node *list, t_arg *new_node);
int ft_handle_redirection(char *input, int *i, int *ss_quot);
/////////////////////////////////Pour le free//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int strequ(char *s1, char *s2);


#endif
