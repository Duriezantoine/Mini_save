/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/23 15:21:15 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
#include "errno.h"

void print_args(char **argv) {
    if (argv == NULL) {
	printf("(null)\n");
	return;
    }
    while (*argv != NULL) {
	printf("|Iciconnar|%s\\n ", *argv);
	argv++;
    }
    printf("\n");
}

void print_env(char **envp) {
    if (envp == NULL) {
	printf("(null)\n");
	return;
    }
    while (*envp != NULL) {
	printf("%s\n", *envp);
	envp++;
    }
}

void	ft_free_double_tab(char **str)
{
	int x;

	x = 0;
	while(str[x])
	{
		free(str[x]);
		x++;
	}
	free(str);
}

char	*ft_getpath(char **env)
{
	while (*env)
	{
		if (strncmp(*env, "PATH=", 5) == 0)
			return *env + 5;
		env++;
	}
	return NULL;
}
static char	*create_full_path(char **split_path, char *str, int i)
{
	char	*demi_path;
	char	*full_path;

	demi_path = ft_strjoin(split_path[i], "/");
	full_path = ft_strjoin(demi_path, str);
	free(demi_path);
	return (full_path);
}

char	*get_path(char *str, char **env)
{
	char	*path;
	char	**split_path;
	char	*full_path;
	int		i;

	path = ft_getpath(env);
	if (!path)
		return ("R");
	split_path = ft_split(path, ':');
	if (!split_path)
		return ("S");
	i = -1;
	while (split_path[++i])
	{
		full_path = create_full_path(split_path, str, i);
		if (access(full_path, F_OK) != -1)
		{
			ft_free_double_tab(split_path);
			return (full_path);
		}
		free(full_path);
	}
	ft_free_double_tab(split_path);
	return (NULL);
}

struct s_exec {
	char *exec;
	char **argv;
	char **envp;
	t_iofile *infile;
	t_iofile *outfile;

	int in;
	int out;
	int pid;
	int	nb_exec;
};

int cdt_len(char **a) {
	if(!a)
		 return 0;
	int i = 0;
	while(a[i]) {
		i++;
	}
	return i;
}



int lst_len(t_node *list) {
	int ret;
	ret  = 0;
	while(list) {
		ret++;
		list = list->next;
	}
	return ret;
}

int env_len(t_env *list) {
	int ret = 0;
	while(list)
	{
		ret++;
		list = list->next;
	}
	return ret;
}

void real_strcat(char *dest, char *src) 
{
	int start ;
	int i ;
	
	i = 0;
	start= ft_strlen(dest);
	while(i < (int)ft_strlen(src)) 
	{
		dest[start + i] = src[i];
		i++; 
	}
	dest[start + i] = 0;
}
static char	*create_env_str(t_env *env)
{
	char	*ret;
	int		len;

	len = ft_strlen(env->key);
	if (env->value)
		len += ft_strlen(env->value) + 2;
	else
		len += 1;
	ret = ft_calloc(len, sizeof(char));
	if (!ret)
		return (NULL);
	real_strcat(ret, env->key);
	if (env->value)
	{
		ret[ft_strlen(env->key)] = '=';
		real_strcat(ret, env->value);
	}
	return (ret);
}

char	**get_env_cdt(t_env *env)
{
	char	**ret;
	int		i;
	t_env	*tmp;

	tmp = env;
	ret = ft_calloc(env_len(env) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (env)
	{
		ret[i] = create_env_str(env);
		if (!ret[i])
			return (NULL);
		i++;
		env = env->next;
	}
	return (ret);
}

static void	free_clone(char **ret, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

char	**clone_cdt(char **table)
{
	char	**ret;
	int		len;
	int		i;

	len = cdt_len(table);
	ret = ft_calloc(len + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = ft_strdup(table[i]);
		if (!ret[i])
		{
			free_clone(ret, i);
			return (NULL);
		}
		i++;
	}
	return (ret);
}


void free_split(char **split) 
{
	int i ;
	
	i = 0;
	if(!split) return;
	while(split[i]) {
		free(split[i]);
		i++;
	}
	free(split);
}

int ft_replace_var(char **str, t_env *env)
{
	char *tmp;
	
	while(env)
	{
		tmp = ft_strjoin("$",env->key);
	    if (strncmp(tmp, (*str), ft_strlen(tmp)) == 0)
		{
			free(str);
			(*str) = env->value;
			return(1);
		}
		env = env->next;
	}
	return(0);

}
static char	*find_path_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	check_path_access(char **split_path, char *str)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(tmp, str);
		free(tmp);
		if (access(full_path, F_OK | X_OK) != -1)
		{
			free(full_path);
			return (1);
		}
		free(full_path);
		i++;
	}
	return (0);
}

int	ft_check_cmd_valid(char *str, t_env *env)
{
	char	*path;
	char	**split_path;
	int		result;

	path = find_path_env(env);
	if (!path)
		return (0);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (0);
	result = check_path_access(split_path, str);
	free_split(split_path);
	return (result);
}

static void	init_exec_struct(struct s_exec *ret, t_node *list, int i, int len)
{
	ret[i].exec = ft_strdup(list->cmd->cmd_and_args[0]);
	ret[i].argv = clone_cdt(list->cmd->cmd_and_args);
	ret[i].nb_exec = len;
	ret[i].infile = list->cmd->input_str;
	ret[i].outfile = list->cmd->output_str;
	ret[i].out = -1;
	ret[i].in = -1;
	ret[i].pid = -1;
}

static void	free_env_array(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

struct s_exec	*lst_to_execs(t_node *list, int *len)
{
	struct s_exec	*ret;
	int				i;
	char			**env;

	*len = lst_len(list);
	ret = ft_calloc(*len, sizeof(struct s_exec));
	if (!ret)
		return (NULL);
	env = get_env_cdt(list->env);
	i = 0;
	while (list)
	{
		init_exec_struct(ret, list, i, *len);
		ret[i].envp = clone_cdt(env);
		i++;
		list = list->next;
	}
	free_env_array(env);
	return (ret);
}

struct s_ituple {
	int idx;
	int len;
};

int ft_fork(int exit_err, void (*func)(struct s_exec *, int, int), struct s_exec *data, struct s_ituple il) {
	int pid;

	if(!func)
		return -1;
	pid = fork();
	if(pid < 0)
		return -1;
	if(pid == 0) {
		func(data, il.idx, il.len);
		exit(exit_err);
	}
	return pid;
}

int ft_wait_all(struct s_exec *execs, int len) {
    int i;
    int status;
    int last_exit_status;

	last_exit_status = -1;
	status = 0;
    for (i = 0; i < len; i++) {
		if (ft_exceve_bulting(execs[i].argv[0], 1))
		{
			if (waitpid(execs[i].pid, &status, 0) == -1)
				perror("waitpid");
			if (WIFEXITED(status)) {
				last_exit_status = WEXITSTATUS(status);
			} else if (WIFSIGNALED(status)) {
				last_exit_status = 128 + WTERMSIG(status);
				if (last_exit_status == 130 || last_exit_status == 131)
					write(2, "\n", 2);
			}
		}
    }
    return (last_exit_status);
}

static void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_iofile_list(t_iofile *file)
{
	t_iofile	*tmp;

	while (file)
	{
		free(file->file);
		tmp = file->next;
		free(file);
		file = tmp;
	}
}

void	free_exec(struct s_exec e)
{
	free(e.exec);
	free_str_array(e.argv);
	free_str_array(e.envp);
	if (e.in > 2)
		close(e.in);
	if (e.out > 2)
		close(e.out);
	free_iofile_list(e.infile);
	free_iofile_list(e.outfile);
}

void free_all_exec(struct s_exec *execs, int len) {
	int i;
	i = 0;
	while(i < len) {
		free_exec(execs[i]);
		i++;
	}
	free(execs);
}


struct s_exec dup_exec(struct s_exec e) {
	struct s_exec ret;
	int i;

	ret.exec = ft_strdup(e.exec);
	ret.argv = ft_calloc(cdt_len(e.argv) + 1, sizeof(char *));
	ret.envp = ft_calloc(cdt_len(e.envp) + 1, sizeof(char *));
	i = 0;
	while(ret.argv && e.argv[i]) {
		ret.argv[i] = ft_strdup(e.argv[i]);
		i++;
	}
	i = 0;
	while(ret.envp && e.envp[i]) {
		ret.envp[i] = ft_strdup(e.envp[i]);
		i++;
	}
	ret.in = e.in;
	ret.out = e.out;
	return ret;
}

int strequ(char *s1, char *s2) {
	return strcmp(s1, s2) == 0;
}

int builtin(char *name) {

	int founded = 0;
	if (name == NULL)
		return (-1);
	if(strequ(name, "env"))
		founded = 1;
	if(strequ(name, "echo"))
		founded = 2;
	if(strequ(name, "export"))
		founded = 3;
	if(strequ(name, "cd"))
		founded = 4;
	if(strequ(name, "unset"))
		founded = 5;
	if(strequ(name, "pwd"))
		founded = 6;
	if(strequ(name, "exit"))
		founded = 7;
	return founded;
}

int exec(char *name, char **argv, char ***envp) {
	int i;
	int built;
	
	i = 0;
	built = builtin(name );
	if(!builtin(name))
	{
		if (!strchr(name, '/'))
			name = get_path(name, *envp);
		if (name)
		{
			execve(name, argv, (*envp));
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			if (errno == 13)
				return (126);
		}
		return(127);
	}
	return(0);
}

void	sort_envp_ex(char **copy_envp)
{
	char	*tmp;
	int		num_envp;
	int 	i;
	int		j;

	num_envp = 0;
	while (copy_envp[num_envp] != NULL)
		num_envp++;
	i = -1;
	while (++i < num_envp - 1)
	{
		j = -1;
		while (++j < num_envp - i - 1)
		{
			if (strcmp(copy_envp[j], copy_envp[j + 1]) > 0)
			{
				tmp = copy_envp[j];
				copy_envp[j] = copy_envp[j + 1];
				copy_envp[j + 1] = tmp;
			}
		}
	}
}
void	ft_display_envp(char *copy_envp[])
{
	int		i;
	char	*sep;

	i = -1;
	sort_envp_ex(copy_envp);
	while (copy_envp[++i])
	{
		if (strncmp(copy_envp[i], "_=", 2) != 0 && strncmp(copy_envp[i], "_\0", 2) != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			sep = strchr(copy_envp[i], '=');
			if (sep)
			{
				*sep = '\0';
				ft_putstr_fd(copy_envp[i], 1);
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(sep + 1, 1);
				ft_putstr_fd("\"", 1);
				*sep = '=';
			}
			else
				ft_putstr_fd(copy_envp[i], 1);
			ft_putstr_fd("\n", 1);
		}
	}
}

void	ft_start_unset(struct s_exec **lst, t_node **list, int i)
{
	char **old;

	bulting_unset( &lst[i]->envp,(*list)->cmd,(*list));
	old = lst[i]->envp;
	lst[i]->envp = get_env_cdt((*list)->env);
	ft_free_double_tab(old);
}

int	ft_choose_export(struct s_exec **lst, int i, int *ret)
{
	if((*lst)->argv[1]==NULL)
		ft_display_envp((*lst)[i].envp);
	else if ((*lst)[i].nb_exec == 1)
		*ret = bulting_export((*lst)[i].argv, &(*lst)[i].envp);
	else
		return (1);
	return (0);
}

int ft_excev_butlin(struct s_exec **lst, t_node **list, int i, t_data *data)
{        
	int built = 0;
	int ret = 0;

	built = builtin((*lst)[i].exec);
	if (built == -1)
		return (0);
	if (built == 1) 
		return (bulting_env((*list)));
	if (built == 2) 
		return (bulting_echo((*lst)[i].argv,1));
	if (built == 3)
		if (ft_choose_export(lst, i, &ret))
			return (1);
	if (built == 4) 
	      ret =  bulting_cd((*lst)[i].argv,(*list),  &(*list)->env);
	if (built == 5 && i ==0) 
		ft_start_unset(lst, list, i);
	if (built == 6) 
		bulting_pwd();
	if (built == 7 )
		return bulting_exit((*lst)[i].argv,(*list),  &(*list)->env, data);
	ft_free_env(&(*list)->env);
	(*list)->env = ft_insert_env(lst[i]->envp);
	return (ret);
}

void handler_void(int sig)
{
	(void) sig;
}

int	open_in(struct s_exec *exec)
{
	int			oflags;
	t_iofile	*tmp;

	while (exec->outfile)
	{
		if (exec->out > 1)
			close(exec->out);
		oflags = O_WRONLY | O_CREAT;
		if (exec->outfile->type == APPEND)
			oflags |= O_APPEND;
		else
			oflags |= O_TRUNC;
		
		exec->out = open(exec->outfile->file, oflags, 0644);
		if (exec->out < 0)
		{
			perror("open");
			return (1);
		}
		tmp = exec->outfile;
		exec->outfile = tmp->next;
		free(tmp->file);
		free(tmp);
	}
	return (0);
}

int	open_in_out(struct s_exec *exec)
{
	t_iofile	*tmp;

	if (open_in(exec))
		return (1);
	while (exec->infile)
	{
		if (exec->in > 0)
			close(exec->in);
		exec->in = open(exec->infile->file, O_RDONLY);
		if (exec->in < 0)
		{
			perror("open");
			return (1);
		}
		tmp = exec->infile;
		exec->infile = tmp->next;
		free(tmp->file);
		free(tmp);
	}
	return (0);
}

typedef struct s_exec_info
{
	int len;
	int last_in;
	int p[2];
	int ret;
	int i;

	t_env **env;
}	t_exec_info;


void	ft_execve_built_exit(t_exec_info *info, struct s_exec *lst,
						t_node *list)
{
	ft_free_env(&(list->env));
	free_all_exec(lst, info->len);
	if (info->last_in > 0)
		close(info->last_in);
	if (info->i < info->len - 1)
	{
		close(info->p[1]);
		info->last_in = info->p[0];
	}
	ft_free_return_loop(list);
	ft_free_end(list, info->env);
	exit(info->ret);
}

void	ft_execve_dup_io(t_exec_info *info, struct s_exec *lst)
{
	if (lst[info->i].in != 0)
	{
		dup2(lst[info->i].in, 0);
		close(lst[info->i].in);
	}
	if (lst[info->i].out != 1)
	{
		dup2(lst[info->i].out, 1);
		close(lst[info->i].out);
	}
}

void	ft_execve_built(t_exec_info *info, struct s_exec *lst,
					t_node *list, t_data *data)
{
	if (open_in_out(&lst[info->i]) != 0)
		info->ret = 1;
	else
	{
		int stdin_copy = dup(0);
		int stdout_copy = dup(1);
		ft_execve_dup_io(info, lst);
		info->ret = ft_excev_butlin(&lst, &list, info->i, data);
		dup2(stdin_copy, 0);
		dup2(stdout_copy, 1);
		close(stdin_copy);
		close(stdout_copy);
		if (lst[info->i].argv[0] != NULL
			&& strequ(lst[info->i].argv[0], "exit") && info->len == 1)
		{
			if (info->ret == -1)
				info->ret = 1;
			else
				ft_execve_built_exit(info, lst, list);
		}
	}
}

void	ft_execve_bin_child(t_exec_info *info, struct s_exec *lst,
					t_node *list)
{
	if (info->i < info->len - 1)
		close(info->p[0]);
	int exit_code = open_in_out(&lst[info->i]);
	if (exit_code == 0)
	{
		ft_execve_dup_io(info, lst);
		exit_code = exec(lst[info->i].exec,
			lst[info->i].argv, &lst[info->i].envp);
	}
	ft_free_env(&(list->env));
	free_all_exec(lst, info->len);
	if (info->last_in > 0)
		close(info->last_in);
	if (info->i < info->len - 1)
	{
		close(info->p[1]);
		info->last_in = info->p[0];
	}
	ft_free_return_loop(list);
	ft_free_end(list, info->env);
	exit(exit_code);
}

void	ft_init_execve(t_exec_info *info, struct s_exec **lst,
					t_node *list, t_env **env)
{
	*lst = lst_to_execs(list, &(info->len));
	info->last_in = 0;
	info->ret = -1;
	info->env = env;
	signal(SIGQUIT, handler_void);
	signal(SIGINT, handler_void);
	info->i = -1;
}

int	ft_manage_pipe(t_exec_info *info, struct s_exec *lst)
{
	if (info->i < info->len - 1 && pipe(info->p) < 0)
	{
		ft_putstr_fd("Erreur: Échec de la création du pipe.\n", 2);
		return (1);
	}
	if (lst[info->i].in < 0)
		lst[info->i].in = info->last_in;
	if (lst[info->i].out < 0)
	{
		if (info->i < info->len - 1)
			lst[info->i].out = info->p[1];
		else
			lst[info->i].out = 1;
	}
	return (0);
}

int	ft_exec_cmd(t_exec_info *info, struct s_exec *lst, t_node *list, t_data *data)
{
	
	if (ft_exceve_bulting(lst[info->i].argv[0], info->len) == 0)
		ft_execve_built(info, lst, list, data);
	else
	{
		lst[info->i].pid = fork();
		if (lst[info->i].pid < 0)
		{
			fprintf(stderr, "Erreur: Échec du fork.\n");
			return (1);
		}
		else if (lst[info->i].pid == 0)
			ft_execve_bin_child(info, lst, list);
	}
	return (0);
}

int ft_exceve(t_node *list, t_data *data, t_env **env)
{
	t_exec_info	info;
    struct s_exec *lst;
	int rete;

	ft_init_execve(&info, &lst, list, env);
	while (++info.i < info.len)
	{

		if (ft_manage_pipe(&info, lst) || ft_exec_cmd(&info, lst, list, data))
			break;
		if (info.last_in > 0)
			close(info.last_in);
		if (info.i < info.len - 1)
		{
			close(info.p[1]);
			info.last_in = info.p[0];
		}
    }
    rete = ft_wait_all(lst, info.len);
	if (rete != -1)
		info.ret = rete;
	ft_free_env(&(list->env));
    list->env = ft_insert_env(lst[0].envp);
    free_all_exec(lst, info.len);
    return info.ret;
}
