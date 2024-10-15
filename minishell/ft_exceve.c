/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/15 16:57:59 by aduriez          ###   ########.fr       */
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
char *get_path(char *str)
{
    char *path;
    char **split_path;
    char *full_path;
    int i;
//   printf("Je suis a la rechercher du chemin");
    path = getenv("PATH");
    if (!path) {
	fprintf(stderr, "Erreur: La variable d'environnement PATH n'est pas définie.\n");
	return("R");
    }

    split_path = ft_split(path, ':');
    if (!split_path) {
	fprintf(stderr, "Erreur: Impossible de diviser le chemin.\n");
	return("S");
    }

    i = 0;
    while (split_path[i])
    {
		char *demi_path = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(demi_path, str);
		free(demi_path);

		if (access(full_path, F_OK) != -1)
		{
		//     printf("Chemin trouvé: %s\n", full_path);
			// free_split(split_path);
		//     printf("Chemin non trouvé pour: %s\n", str);
			ft_free_double_tab(split_path);
			return(full_path);
		}
		free(full_path);
		i++;
    }
	ft_free_double_tab(split_path);
	fprintf(stderr, "Command '%s' not found\n", str);
//     printf("\nCommand not valid\n");
    return(NULL);
    // free_split(split_path);
}

struct s_exec {
	char *exec;
	char **argv;
	char **envp;
	int in;
	int out;
	int pid;
};

int cdt_len(char **a) {
	if(!a) return 0;
	int i = 0;
	while(a[i]) {
		i++;
	}
	return i;
}



int lst_len(t_node *list) {
	int ret = 0;
	while(list) {
		ret++;
		list = list->next;
	}
	return ret;
}

int env_len(t_env *list) {
	int ret = 0;
	while(list) {
		ret++;
		list = list->next;
	}
	return ret;
}

void real_strcat(char *dest, char *src) {
	int start = ft_strlen(dest);
	int i = 0;
	while(i < (int)ft_strlen(src)) {
		dest[start + i] = src[i];
		i++; // Correction: Ajout de l'incrémentation de i
	}
	dest[start + i] = 0;
}


char **get_env_cdt(t_env *env) {
    int len = env_len(env);
    char **ret = ft_calloc(len + 1, sizeof(char *));
    if (!ret) return NULL;
    int count;

    count = 0;
	t_env *tmp;
    int i = 0;
	tmp =env;
    while (env) {
	
	ret[i] = ft_calloc(ft_strlen(env->key) + ft_strlen(env->value) + 2, sizeof(char));
	// if (!ret[i]) {
	//     // Libérer toutes les chaînes de caractères allouées précédemment
	//     for (int j = 0; j < i; j++) {
	//         free(ret[j]);
	//     }
	//     free(ret); // Libérer le tableau lui-même
	//     return NULL;
	// }
	real_strcat(ret[i], env->key);
	ret[i][ft_strlen(env->key)] = '='; // Ajout direct du caractère '='
	real_strcat(ret[i], env->value);
	i++;
	env = env->next;
    }
    return ret;
}

char **clone_cdt(char **table) {
	int len = cdt_len(table);
	char **ret = ft_calloc(len + 1, sizeof(char *));
	if(!ret) return NULL;
	int i = 0;
	while(i < len) {
		ret[i] = ft_strdup(table[i]);
		if(!ret[i]) {
			int j = 0;
			while(j < i) {
				free(ret[j]);
				j++;
			}
			free(ret); // Correction: Libération de ret
			return NULL;
		}
		i++;
	}
	return ret;
}

void free_split(char **split) {
	int i = 0;
	if(!split) return;
	while(split[i]) {
		free(split[i]);
		i++;
	}
	free(split);
}

char *get_program_name(char *name, int builtin) 
{
	if(builtin) return ft_strdup(name);
	char *path;
	char **split_path;
	char *full_path = NULL; // Correction: Initialisation de full_path
	int i;

	path = getenv("PATH");
	if (!path) 
	{
		fprintf(stderr, "Erreur: La variable d'environnement PATH n'est pas définie.\n");
		return NULL;
	}

	split_path = ft_split(path, ':');
	if (!split_path) {
		fprintf(stderr, "Erreur: Impossible de diviser le chemin.\n");
		return NULL;
	}

	i = 0;
	while (split_path[i])
	{
		char *tmp = ft_strjoin(split_path[i], "/");
		full_path = ft_strjoin(tmp, name); // Correction: Utilisation de tmp au lieu de full_path
		free(tmp);

		if (access(full_path, F_OK | X_OK) != -1)
		{
			free_split(split_path);
			return full_path;
		}

		free(full_path);
	       // full_path = NULL; // Correction: Réinitialisation de full_path
		i++;
	}
	printf("\nCOmmande not Valid\n");
	free_split(split_path);
	return NULL;
}

int ft_replace_var(char **str, t_env *env)
{
	//Pas dur que ca modifier la variables il faut alors verfifier 
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
int ft_check_cmd_valid(char *str, t_env *env)
{
    char *path;
    char **split_path;
    char *full_path;
    int i;

    path = NULL;
    while (env)
    {
	if (ft_strcmp(env->key, "PATH") == 0)
	{
	    path = env->value;
	    break;
	}
	env = env->next;
    }

    if (!path)
    {
	fprintf(stderr, "Erreur: La variable d'environnement PATH n'est pas définie.\n");
	return 0;
    }

    split_path = ft_split(path, ':');
    if (!split_path)
    {
	fprintf(stderr, "Erreur: Impossible de diviser le chemin.\n");
	return 0;
    }

    i = 0;
    while (split_path[i])
    {
	full_path = ft_strjoin(split_path[i], "/");
	full_path = ft_strjoin(full_path, str);
	if (access(full_path, F_OK | X_OK) != -1)
	{
	    free_split(split_path);
	    free(full_path);
	    return 1; // La commande est valide
	}
	free(full_path);
	i++;
    }

    free_split(split_path);
    return 0; // La commande n'est pas valide
}

struct s_exec *lst_to_execs(t_node *list, int *len) {
	*len = lst_len(list);
	struct s_exec *ret = ft_calloc(*len, sizeof(struct s_exec)); // Correction: Suppression du cast (size_t)
	if(!ret) return NULL;
	char **env = get_env_cdt(list->env);
	t_env *tmp;
	tmp = list->env;//Ce  qui permet de garder la lise chaine pour le FT_REPLACE_var
	int i = 0;
	while(list) {
		ret[i].exec = get_program_name(list->cmd->cmd_and_args[0], list->cmd->is_builtin);
		ret[i].argv = clone_cdt(list->cmd->cmd_and_args);
		ret[i].envp = clone_cdt(env);
		//Verification pour la commande
		// if (ret[i].exec != NULL)
		//         if (ret[i].exec[0]== '$')
		//                 if(ft_replace_var(&ret[i].exec, tmp)==1)
		//                         printf("La variable recherche n'existe pas ");
		//Verification pour les arguments
		ret[i].in = list->cmd->input;
		ret[i].out = list->cmd->output;
		ret[i].pid = -1;
		// if(ft_check_cmd_valid(ret[i].exec, tmp)==0)
		//         printf("Command \'%s\' not found\n", ret[i].exec);
		i++;
		list = list->next;
	}
	i=0;
	while(env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return ret;
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
    int last_exit_status = 0;
status = 0;
    for (i = 0; i < len; i++) {
	if (waitpid(execs[i].pid, &status, 0) == -1) {
	    perror("waitpid");

	}
	if (WIFEXITED(status)) {
	    last_exit_status = WEXITSTATUS(status);
	} else if (WIFSIGNALED(status)) {
	//     fprintf(stderr, "Command terminated by signal %d\n", WTERMSIG(status));
	    last_exit_status = 128 + WTERMSIG(status);
	}
    }
    return last_exit_status;
}

void free_exec(struct s_exec e) {
	free(e.exec);
	int i = 0;
	while(e.argv[i]) {
		free(e.argv[i]);
		i++;
	}
	free(e.argv); // Correction: Libération de e.argv
	i = 0;
	while(e.envp[i]) {
		free(e.envp[i]); // Correction: Utilisation de e.envp au lieu de e.argv
		i++;
	}
	free(e.envp); // Correction: Libération de e.envp
	if(e.in > 2) close(e.in);
	if(e.out > 2) close(e.out);
}

void free_all_exec(struct s_exec *execs, int len) {
	int i;
	i = 0;
	while(i < len) {
		free_exec(execs[i]);
		i++;
	}
	free(execs); // Correction: Libération de execs
}


struct s_exec dup_exec(struct s_exec e) {
	struct s_exec ret;
	ret.exec = ft_strdup(e.exec);
	ret.argv = ft_calloc(cdt_len(e.argv) + 1, sizeof(char *)); // Correction: +1 pour le NULL terminal
	ret.envp = ft_calloc(cdt_len(e.envp) + 1, sizeof(char *)); // Correction: +1 pour le NULL terminal
	int i = 0;
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
	if(strequ(name, "env")) {
		printf("env\n");
		founded = 1;
	}
		if(strequ(name, "echo")) {
		printf("3env\n");
		founded = 2;
	}
		if(strequ(name, "export")) {
		// printf("env\n");
		founded = 3;
	}
		if(strequ(name, "cd")) {
		// printf("env\n");
		founded = 4;
	}
		if(strequ(name, "unset")) {
		// printf("env\n");
		founded = 5;
	}
		if(strequ(name, "pwd")) {
		// printf("env\n");
		founded = 6;
	}
			if(strequ(name, "exit")) {
		// printf("env\n");
		founded = 7;
	}
	printf("\nJe suis found|%d|\n", founded);
	return founded;
}

int exec(char *name, char **argv, char ***envp) {
	int i;
	i = 0;
	int built;
       built = builtin(name );
//        printf("\nJe suis built|%d|\n", built);
	if(!builtin(name))
	{                   // Imprimer name
			// printf("\nPasse a cote du bulting\n");
		name = get_path(name);
		if (name)
		{
			execve(name, argv, (*envp));
			fprintf(stderr, "%s: %s\n", name, strerror(errno));
		}
		return(0);
	}
	// print_env((*envp));
	return(0);
}
void	sort_envp_ex(char **copy_envp)
{
	char	*tmp;
	int		num_envp;

	int i, j;
	num_envp = 0;
	// Calculer le nombre d'éléments dans copy_envp
	while (copy_envp[num_envp] != NULL)
		num_envp++;
	// Tri à bulles (bubble sort) basé sur strcmp
	for (i = 0; i < num_envp - 1; i++)
	{
		for (j = 0; j < num_envp - i - 1; j++)
		{
			if (strcmp(copy_envp[j], copy_envp[j + 1]) > 0)
			{
				// Échanger les pointeurs
				tmp = copy_envp[j];
				copy_envp[j] = copy_envp[j + 1];
				copy_envp[j + 1] = tmp;
			}
		}
	}
}
void	ft_display_envp(char *copy_envp[])
{
	int	i;

	i = 0;
	sort_envp_ex(copy_envp);
	//printf("\n 1er|%s|\n", copy_envp[0]);
	while (copy_envp[i])
	{
		    if (strncmp(copy_envp[i], "_=", 2) != 0 && strncmp(copy_envp[i], "_\0", 2) != 0) 
				printf("declare -x %s\n", copy_envp[i]);
		i++;
	}
}

int ft_excev_butlin(struct s_exec **lst, t_node **list, int i)
{        
	int built = 0;
    //    printf("|Name=|%s|I=|%d|",  (*lst)[i].exec, i);
       built = builtin((*lst)[i].exec) ;
		if (built == 1) 
	{
		// printf("Je susi bulting Env");
	       bulting_env((*list));
 
	}   
	if (built == 2) 
	{
		// printf("\nJe susi bulting echo\n");
		bulting_echo((*lst)[i].argv,1);
		return(0);
	}
	 if (built == 3 && i==0) 
	{
		// printf("Je susi bulting Export");
		//  print_args(lst[i]->argv);
		 if((*lst)->argv[1]==NULL)
		 	ft_display_envp((*lst)[i].envp);
		else
	       bulting_export((*lst)[i].argv, &(*lst)[i].envp);
 
	}         
	if (built == 4) 
	{
		// printf("Je susi bulting Cd");
	       bulting_cd((*lst)[i].argv,(*list),  &(*list)->env);
 
	}
	if (built == 5 && i ==0) 
	{
		// printf("Je susi bulting Unset");
	       bulting_unset( &lst[i]->envp,(*list)->cmd,(*list));
		 //Penser a free ici;
		char **old = lst[i]->envp;
		lst[i]->envp=get_env_cdt((*list)->env);
		ft_free_double_tab(old);
		
	}
	if (built == 6) 
	{
		// printf("Je susi bulting Pwd");
		bulting_pwd();
	}
	if (built ==7) 
	{
		// printf("Je susi bulting Cd");
	       return bulting_exit((*lst)[i].argv,(*list),  &(*list)->env);
 
	}
	
	ft_free_env(&(*list)->env);
	(*list)->env = ft_insert_env(lst[i]->envp);
	// print_env_list((*list)->env);
	return(0);
}
int ft_exceve(t_node *list, t_data *data, t_env **env)
{
    int len;
    struct s_exec *lst = lst_to_execs(list, &len);
    int last_in = 0, p[2], ret = -1;
    (void)data;
    (void)env;

    for (int i = 0; i < len; i++)
    {
	if (i < len - 1 && pipe(p) < 0)
	{
	    fprintf(stderr, "Erreur: Échec de la création du pipe.\n");
	    break;
	}

	lst[i].in = (lst[i].in < 0) ? last_in : lst[i].in;
	lst[i].out = (lst[i].out < 0) ? ((i < len - 1) ? p[1] : 1) : lst[i].out;

	if (ft_exceve_bulting(lst[i].argv[0], i) == 0)
	{
	    // Traitement des builtins
	    int stdin_copy = dup(0);
	    int stdout_copy = dup(1);

	    if (lst[i].in != 0)
			dup2(lst[i].in, 0);
	    if (lst[i].out != 1)
			dup2(lst[i].out, 1);
		ret = ft_excev_butlin(&lst, &list, i);
		dup2(stdin_copy, 0);
	    dup2(stdout_copy, 1);
	    close(stdin_copy);
	    close(stdout_copy);
		if (strequ(lst[i].argv[0], "exit"))
		{
			if (ret == -1)
				ret = 1;
			else
			{
				ft_free_env(&(list->env));
				free_all_exec(lst, len);
				if (last_in > 0)
					close(last_in);
				if (i < len - 1)
				{
				close(p[1]);
				last_in = p[0];
				}
				ft_free_return_loop(list, data);
				ft_free_end(list, env, NULL);
				exit(ret);
			}
		}
	}
	else
	{
	    // Traitement des commandes non-builtin
	    lst[i].pid = fork();
	    if (lst[i].pid < 0)
	    {
		fprintf(stderr, "Erreur: Échec du fork.\n");
		break;
	    }
	    else if (lst[i].pid == 0)
	    {
		if (i < len - 1)
		    close(p[0]);
		
		if (lst[i].in != 0)
		{
		    dup2(lst[i].in, 0);
		    close(lst[i].in);
		}
		if (lst[i].out != 1)
		{
		    dup2(lst[i].out, 1);
		    close(lst[i].out);
		}
		int exit_code = exec(lst[i].exec, lst[i].argv, &lst[i].envp);
		ft_free_env(&(list->env));
		free_all_exec(lst, len);
		if (last_in > 0)
	    	close(last_in);
		if (i < len - 1)
		{
	   	 close(p[1]);
	   	 last_in = p[0];
		}
		ft_free_return_loop(list, data);
		 ft_free_end(list, env, NULL);
		exit(exit_code);
	    }
	}

	// Nettoyage des descripteurs de fichiers
	if (last_in > 0)
	    close(last_in);
	if (i < len - 1)
	{
	    close(p[1]);
	    last_in = p[0];
	}
    }

    // Attendre la fin de tous les processus non-builtin
    ret = ft_wait_all(lst, len);
	ft_free_env(&(list->env));
    list->env = ft_insert_env(lst[0].envp);
    free_all_exec(lst, len);
	printf("%d\n", ret);
    return ret;
}