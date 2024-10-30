/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:05:05 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/29 16:40:35 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_insert_data
{
	char						*input;
	int							*i;
	int							iterator;
	char						c;
}								t_insert_data;

extern volatile sig_atomic_t	g_signal_recu;

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
}								t_token;

/// Strucuture pour l'environnement  ////////////////
typedef struct s_env
{
	char						*key;
	char						*value;
	struct s_env				*next;

}								t_env;

typedef struct s_arg
{
	char						*str_command;
	int							type;
	int							quot;
	struct s_arg				*prev;
	struct s_arg				*next;
}								t_arg;

typedef struct s_iofile
{
	char						*file;
	t_token						type;
	struct s_iofile				*next;
}								t_iofile;

typedef struct s_verif_input
{
	int							nbr_stack;
	int							pipe;
	int							alnum;
	int							x;
	char						c;
	int							nbr_token;
	int							token_right;
	int							token_left;
	int							stack_start;
	int							heredoc;
	int							last_char_special;
	int							command_before_pipe;
}								t_verif_input;

typedef struct s_cmd
{
	char						**cmd_and_args;
	t_iofile					*input_str;
	t_iofile					*output_str;
	enum e_tokens				_out_type;
	int							cmd;
	int							is_builtin;
	struct s_cmd				*next;
	struct s_cmd				*prev;
}								t_cmd;

typedef struct s_node
{
	struct s_arg				*arg;
	struct s_cmd				*cmd;
	struct s_env				*env;

	int							pipe[2];

	struct s_node				*prev;
	struct s_node				*next;

}								t_node;

typedef struct s_here_doc_data
{
	char						*write_here_do;
	int							ret;
	int							test;
	struct sigaction			action;
	struct termios				term_attr;
	char						*temp_file_name;
	int							tmp_fd;
	t_node						*list;
}								t_here_doc_data;

// Pour le parsing

typedef struct s_token_str_two
{
	char						*str;
	char						*token;

}								t_token_str_two;

typedef struct s_save
{
	char						*str;
	int							bool;
	struct s_save				*next;

}								t_save;

typedef struct s_command
{
	char						**input_split;
	t_token_str_two				*name;
	int							b;

}								t_command;

typedef struct s_ituple
{
	int							idx;
	int							len;
}								t_ituple;
/////////////////////////////////////////Utils pour le parsing//////////////////
typedef struct s_data
{
	int							nbr_command;
	char						count;
	int							bool;
	int							exit_code;
}								t_data;

typedef struct s_str
{
	char						*str;
	int							order;
	int							bool;
}								t_str;

typedef struct s_echo
{
	int							s_quot;
	int							w_quot;

	t_str						*str_w_quot;
	t_str						*str_s_quot;
	int							order_occurence;
}								t_echo;

typedef struct s_exec_info
{
	int							len;
	int							last_in;
	int							p[2];
	int							ret;
	int							i;

	t_env						**env;
}								t_exec_info;

typedef struct s_exec
{
	char						*exec;
	char						**argv;
	char						**envp;
	t_iofile					*infile;
	t_iofile					*outfile;

	int							in;
	int							out;
	int							pid;
	int							nb_exec;
}								t_exec;

typedef struct s_split_datas
{
	int							in_quotes;
	int							in_single_quotes;
	int							j;
	int							k;
}								t_split_datas;

typedef struct s_split_data
{
	int							count;
	int							j;
	int							in_quotes;
}								t_split_data;

char							*ft_strchr(const char *s, int c);

int								ft_strncmp(const char *str1, const char *str2,
									size_t n);

int								ft_butlin_first(struct s_exec **lst,
									t_node **list, int i, int built);
int								ft_butlin_second(struct s_exec **lst,
									t_node **list, int i, int built);

char							*ft_read_input(t_data *data);
int								ft_process_command(char *input, t_node *list,
									t_data *data, t_env *env);
int								handle_empty_input(char *input, t_data *data);
void							setup_signals(void);

int								main(int argc, char **argv, char **envp);
int								shell_loop(t_node *list, t_data *data,
									t_env **env);
int								ft_search_inputs(char *str);
int								ft_orga_verif_input(char *str);
int								ft_white_spaces(char *str);
void							ft_insert_cmd(t_command **command,
									t_data **data, char *input);
void							free_tokens(char **tokens, int len);
void							ft_insert_token(t_command **command,
									t_data **data);
void							ft_verif_token(t_command **command,
									t_data **data);
int								count_dollars(char *str);
int								count_segments(char *str);
char							**allocate_result(int len);
int								ft_init_token_space(t_echo *data_echo,
									char *input, int i);
char							*ft_change_save_v3(char *str, t_env *env,
									char c, t_data *data);
// Exits
int								ft_putstr_fd(char *str, int fd);
void							ft_out_exit(int i);
void							ft_inser_init_list_arg(t_node **list);
void							free_list(t_save *head);
void							process_quotes(char *str, int *i, int *c,
									int *y);
void							init_values(int *i, int *c, int *y, char *g);
int								ft_search_var_env(char **save, t_env *env,
									t_data *data);
void							handle_end_of_file(char *limiteur);
int								handle_write_error(t_here_doc_data *here_data);
void							clean_and_exit(t_here_doc_data *data,
									int exit_code);
void							heredoc_handle_sig(int signal);
t_here_doc_data					*get_hd_data(void);
void							read_input(t_here_doc_data *here_doc_data);
char							*close_and_return_temp_file(t_here_doc_data *h);
t_here_doc_data					init_here_doc_data(void);
void							setup_here_doc_files(t_here_doc_data *here_data,
									t_data *data, t_node *list,
									char *write_here_do);
char							*create_file_name(char *temp_file_name,
									t_data *data, char *write_here_do);
int								open_file_here_doc(int tmp_fd,
									char *temp_file_name, char *write_here_do);
int								ft_handle_redirection(char *input, int *i,
									int *ss_quot);
int								ft_nbr_quot(char *input, int i);
int								ft_change_var_environnement(char **str,
									t_env *env, t_data *data);
int								ft_search_quot(char *input);
int								ft_init_token_space(t_echo *data_echo,
									char *input, int i);
int								check_end_of_input(char c, t_echo *data_echo,
									int *ss_quot, int *wt_quot);

int								ft_init_token_space(t_echo *data_echo,
									char *input, int i);
int								ft_handle_quotes(char *input, int *i,
									int *wt_quot, char c);
void							ft_handle_alphanumeric(char *input, int *i,
									int *ss_quot, int x);
void							ft_verif_cmd(t_cmd **list, t_arg *list_arg);
int								ft_insert_cmd_here_doc(t_node *list,
									t_arg *list_arg, t_data *data,
									t_node *base_node);
void							ft_init_cmd(t_cmd **list);
char							*find_env_value(char *save, t_env *env);
// Utils
void							*ft_memset(void *s, int c, size_t n);
int								ft_strlen(char *str);
char							*ft_strjoin(char const *s1, char const *s2);
void							*ft_calloc(size_t elementCount,
									size_t elementSize);
void							*ft_bzero(void *s, size_t n);
char							*ft_strdup(char *src);
int								ft_isalnum(int c);
// Parsing
void							ft_init_tab_echo_malloc(t_echo *data_echo,
									char *input, int i);
int								ft_nbr_quot(char *input, int i);
char							**ft_parsing_init(t_data *data, char *input);
int								ft_parsing(t_node *list, t_data *data,
									char *input, t_env *env);
char							**split_string(char *str, int *len);
int								ft_init_token_space(t_echo *data_echo,
									char *input, int i);
void							ft_init_echo_malloc(t_echo *data_echo);
void							ft_insert_data_w_quot(t_echo *data_echo,
									char *input, int *i, int *place_tab_w_quot);
void							ft_insert_data_s_quot(t_echo *data_echo,
									char *input, int *i, int *place_tab_s_quot);
void							ft_insert_data_s_whith_tab(t_echo *data_echo,
									char *input, int *i, int *clef_tab_s_quot);
void							ft_insert_data_w_whith_tab(t_echo *data_echo,
									char *input, int *i, int *clef_tab_w_quot);
void							ft_insert_list(t_node **list,
									t_echo **data_echo);
void							ft_search_built(t_node **list, char **save);
int								ft_split_with_space(t_echo *data_echo,
									char *input);
char							*ft_strcpy(char *dest, char *src);
char							*ft_strcat(char *dest, char src);
void							ft_insert_new_data_with_data(t_save **save,
									t_echo *data_echo, t_env *env);
void							ft_insert_data_data_echo_s(t_save **save,
									t_echo *data_echo, int iterateur_s,
									t_env *env);
int								bulting_echo(char **cmd, int i);
int								get_env_size(t_env *env_list);
void							free_tab_error(char **env_tab, int i);
void							ft_init_data(t_data *data);
void							print_list(t_node *list);
int								ft_strcmp(char *s1, char *s2);
void							type_insert_cmd(t_arg *new_node);
void							ft_format_list(t_arg *arg);
void							ft_insert_tab_echo(t_echo *data_echo,
									char *input, int i);
void							ft_init_data_list(t_node **list);
int								lexer_cmd(t_node *list, t_data *data);
void							print_liste(t_arg *list);
void							ft_insert_double_tab(t_cmd **list,
									t_arg *list_arg);
t_arg							*ft_init_list(t_node *list, t_echo *data_echo,
									t_save *save);
void							lexer(t_node *head);
char							*ft_itoa(int n);
int								ft_white_space(char c);
char							**clone_cdt(char **table);
char							*find_path_env(t_env *env);
void							free_split(char **split);
int								lst_len(t_node *list);
char							**split_string(char *str, int *len);
// Fonction pour free
void							free_t_echo(t_echo *echo);
// Fonction pour le here_doc
void							free_exec(struct s_exec e);

void							handler_void(int sig);
char							*ft_here_doc(t_data *data, t_node *list,
									char *limiteur, t_node *base_node);
// Fonction pour l'environnement
void							ft_init_env(t_env **env);
char							**ft_split(char const *s, char c);
// Ce qui permet de verifier ou j'en suis
void							print_cmd(t_node *list);
void							print_all_cmds(t_node *list);
int								ft_open_infile(t_node **list, char *infile);
// Ce qui permet de mettre en place l'execution
int								ft_exceve(t_node *list, t_data *data,
									t_env **env);
int								ft_exceve_bulting(char *str, int i);
// Cee qui permet de free
void							free_node(t_node *list);
void							ft_free_data_echo(t_echo *data_echo);
void							ft_free_arg(t_arg *tmp);
void							ft_free_cmd(t_cmd *cmd);
///////////////////////////////////////Pour les bultings//////////////////////
////////////////////////////////Pour le bulting cd///////////////////////////
int								ft_simple_cd(char *s, t_env **env);
void							ft_change_env(char *save, t_env ***env);
char							*new_path_cd(char *s, t_env **env);
char							*ft_execute_cd_home(t_env **env, int i);
int								ft_no_cd_(char *s);
char							*save_pwd(t_env **env);
int								ft_exceve_cd(char **cmd_and_args, t_env **env);
////////////////////////////////Pour le bulting echo////////////////////////////
int								ft_search_n(char **cmd, int i);
/////////////////////////////////Pour le bulting pwd////////////////////////////
void							bulting_pwd(void);
/////////////////////////////////Pour le bulting export/////////////////////////
int								bulting_export(char **argv, char ***env);
int								ft_search_key_envp(char **env, char *key);
void							ft_insert_envp(char ***env, char *key,
									char *value);
char							*ft_copy_end(char *str, char c);
char							*ft_copy_start(char *str, char c);
int								ft_verif_export(char *str);
void							ft_delim_envp(char ***env, char *str);
/////////////////////////////////Pour le bulting unset//////////////////////////
int								bulting_unset(char ***env, t_cmd *cmd,
									t_node *list);
int								ft_search_envp(char **env, char *search);
void							ft_delete_unset(t_env **env, char *search);
/////////////////////////////////Pour le bulting env////////////////////////////
int								bulting_env(t_node *list);
void							sort_envp(t_env **env);
t_env							*copy_env(t_env *env);
/////////////////////////////////Pour le bulting exit///////////////////////////
int								bulting_exit(char **args, t_node *list,
									t_env **env, t_data *data);
/////////////////////////////////Pour le free///////////////////////////////////
void							ft_free_end(t_node *list, t_env **env);
void							ft_free_return_loop(t_node *list);
void							ft_free_env(t_env **env);
void							ft_insert_nodes(t_node *list, t_arg *new_node);
int								ft_handle_redirection(char *input, int *i,
									int *ss_quot);
/////////////////////////////////Pour le free///////////////////////////////////
int								strequ(char *s1, char *s2);
char							**ft_add_string_to_array(char **arr, char *str);
int								ft_get_array_size(char **arr);
char							**ft_allocate_new_array(int size);
int								ft_copy_strings(char **new_arr, char **arr,
									int size);
void							ft_free_new_array(char **new_arr, int size);
void							ft_free_array(char **arr);
int								ft_add_new_string(char **new_arr, char *str,
									int size);
int								bulting_cd(char **cmd_and_args, t_node *list,
									t_env **env);
t_env							*ft_insert_env(char **envp);
void							ft_change_var(char ***env, char *str, int x);
// Prototype de la fonction signal_handler
void							signal_handler(int sig);
// Prototype de la fonction check_signal_status
int								check_signal_status(void);
char							*ft_change_input(char *str, t_env *env,
									t_data *data);
int								count_dollars_outside_quotes(char *str);
// char							*ft_change_input_v2(char *save);
char							**ft_split_d(char *str);
int								ft_space_or_null(char *str);
char							*ft_verif_input(char *str);
int								ft_verif_tokens(char *tmp);
char							*ft_execute_cd_home(t_env **env, int i);
char							*save_pwd(t_env **env);
void							ft_search_and_change_envp(char *key, char *str,
									char ***envp);
int								ft_exceve_bulting(char *str, int len);
int								ft_excev_butlin(struct s_exec **lst,
									t_node **list, int i, t_data *data);
void							free_all_exec(struct s_exec *execs, int len);
int								open_in_out(struct s_exec *exec);
void							ft_execve_dup_io(t_exec_info *info,
									t_exec *lst);
int								exec(char *name, char **argv, char ***envp);
struct s_exec					*lst_to_execs(t_node *list, int *len);
void							ft_execve_built(t_exec_info *info, t_exec *lst,
									t_node *list, t_data *data);
int								ft_wait_all(struct s_exec *execs, int len);
void							ft_display_envp(char *copy_envp[]);
void							ft_start_unset(struct s_exec **lst,
									t_node **list, int i);
int								ft_choose_export(struct s_exec **lst, int i,
									int *ret);
int								ft_excev_butlin(struct s_exec **lst,
									t_node **list, int i, t_data *data);
void							handler_void(int sig);
void							sort_envp_ex(char **copy_envp);
char							**get_env_cdt(t_env *env);
void							ft_free_double_tab(char **str);
int								builtin(char *name);
void							ft_start_unset(struct s_exec **lst,
									t_node **list, int i);
int								cdt_len(char **a);
char							**split_string(char *str, int *len);
void							split_string_d(char *str, char **result);
char							*get_path(char *str, char **env);

#endif
