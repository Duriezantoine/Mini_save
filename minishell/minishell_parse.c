/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/19 18:34:01 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// extern volatile sig_atomic_t signal_recu;


#include "minishell.h"
void print_char_array_d(char **array)
{
    if (!array)
        return;

    int i = 0;
    while (array[i])
    {
        printf("%s\n", array[i]);
        i++;
    }
}
void print_cmd(t_node *list) {
    if (list == NULL || list->cmd == NULL) {
        printf("List or cmd is NULL\n");
        return;
    }

	printf("\nNext Node\n");
    printf("Command: |%s| Command: int |%d|\n", list->cmd->cmd_and_args[0], list->cmd->cmd);
	for (int i = 1; list->cmd->cmd_and_args[i] != NULL; i++) {
		printf("Argument %d: %s\n", i, list->cmd->cmd_and_args[i]);
	}
}

// Fonction pour boucler sur tous les nœuds de la liste
void print_all_cmds(t_node *list) {
    t_node *current = list;
    while (current != NULL) {
        print_cmd(current);
        current = current->next;
    }
}
void print_arg_arg(t_arg *head) {
    t_arg *current = head;

    while (current != NULL) {
        printf("str_command: %s, type: %d, quot: %d\n", current->str_command, current->type, current->quot);
        current = current->next;
    }
}

void organisation_shell_loop(t_node *list, t_data *data)
{
	// Declaration des signaux
	shell_loop(list, data, &list->env);
	// free la command_line
}
// Fonction pour afficher le contenu du répertoire courant
void print_directory_contents()
{
    DIR *dir; // Pointeur vers un répertoire
    struct dirent *entry; // Structure pour stocker les entrées du répertoire

    dir = opendir("."); // Ouvre le répertoire courant
    if (dir == NULL) // Vérifie si l'ouverture du répertoire a échoué
    {
        perror("opendir"); // Affiche un message d'erreur
        return;
    }

    while ((entry = readdir(dir)) != NULL) // Lit les entrées du répertoire une par une
    {
        printf("%s\n", entry->d_name); // Affiche le nom de l'entrée
    }

    closedir(dir); // Ferme le répertoire
}

void print_environment(t_env *env)
{
    t_env *current = env;

    while (current != NULL)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

int	ft_white_space(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] != 95 || str[i] != '\n')//IL faudra l'inmplementer plus pour le testeur parsing
			return(1);
	}
	return(0);
}
void print_env_list(t_env *env) 
{
    t_env *current = env;
    while (current != NULL) {
        printf("Key: %s, Value: %s\n", current->key, current->value);
        current = current->next;
    }
}

void split_string_d	(char *str, char **result)
{
   int i, j, k, in_quotes, in_single_quotes;
    char *temp;
    in_quotes = 0;
    in_single_quotes = 0;
    j = 0;
    k = 0;
    temp = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    if (!temp)
        return;

    for (i = 0; str[i]; i++)
    {
        if (str[i] == '"')
            in_quotes = !in_quotes;
        if (str[i] == '\'')
            in_single_quotes = !in_single_quotes;
        if (( str[i] == ' ') && !in_quotes && !in_single_quotes)
        {
            temp[j] = '\0';
            result[k++] = strdup(temp);
            j = 0;
        }
        else
        {
            temp[j++] = str[i];
        }
    }
    temp[j] = '\0';
    result[k++] = strdup(temp);
    free(temp);
}

int count_dollars( char *str)
{
    int count = 0;
    while (*str)
    {
        if (*str == '$')
        {
            count++;
        }
        str++;
    }
    return count;
}

int count_dollar_followed_by_characters(char *str)
{
    int count = 0;
    while (*str)
    {
        if (*(str + 1) && isalnum(*(str + 1)))
        {
            count++;
            while (*(str + 1) && isalnum(*(str + 1)))
            {
                str++;
            }
        }
        str++;
    }
    return count;
}

char **allocate_result(int len)
{
    char **result = (char **)malloc(sizeof(char *) * (len + 1));
    if (!result)
        return NULL;
    result[len] = NULL;
    return result;
}

int count_segments( char *str)
{
    int i, len, in_quotes, in_single_quotes;
    len = 0;
    in_quotes = 0;
    in_single_quotes = 0;
    for (i = 0; str[i]; i++)
    {
        if (str[i] == '"')
            in_quotes = !in_quotes;
        if (str[i] == '\'')
            in_single_quotes = !in_single_quotes;
        if (( str[i] == ' ') && !in_quotes && !in_single_quotes)
            len++;
    }
    return len + 1;
}

char **ft_split_d( char *str)
{
    int len = count_segments(str);
    char **result = allocate_result(len);
    if (result)
        split_string_d(str, result);
    return result;
}
static int	is_quote(char c, int *in_single, int *in_double)
{
	if (c == '\'')
	{
		*in_single = !(*in_single);
		return (1);
	}
	else if (c == '\"')
	{
		*in_double = !(*in_double);
		return (1);
	}
	return (0);
}

int	count_dollars_outside_quotes(char *str)
{
	int	count;
	int	i;
	int	in_single;
	int	in_double;

    // printf("\nIci\n");
	count = 0;
	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
        // printf("\n|STR|%c|\n", str[i]);
		if (!is_quote(str[i], &in_single, &in_double))
		{
			if (str[i] == '$' && !in_single && !in_double)
				count++;
		}
		i++;
	}
    // printf("\ncount|%d|\n",count);
	return (count);
}
int ft_space_or_null(char *str)
{
	int x;
	x=0;
	while(str[x])
	{
		if(str[x] != ' ')
			return(1);
		x++;
	}
	return(0);
}

char    *ft_change_input_v2(char *save)
{
    int x;

    x = 0;
    while(save[x])
    {
        if (save[x]==32)
            x++;
        if(save[x] !=32)
            break;
    }
    return(save);
}

char	*ft_change_input(char **str, t_env *env, t_data *data)
{
	char *tmp_tmp;
	char **tmp;
	char *save_tmp;
	int x;
    char *tmp_tmp_tmp;
	char *save;
	x = 0;
	save_tmp =NULL;
	save = ft_strjoin((*str), " ");
	while (count_dollars_outside_quotes((*str))<=0)
		break;
    tmp_tmp_tmp = ft_change_input_v2(save);
    // printf("save|%s|\n", tmp_tmp_tmp);
	// save = ft_strjoin(str, '$');
	save_tmp = ft_strdup(" ");
	tmp = ft_split_d((save));

	free(save);
	while(tmp[x])
	{
        // printf("saveTMP|%s|\n", tmp[x]);

		if (ft_space_or_null(tmp[x])!=0)
        {
            if (tmp[x][0]== '$')
            {
                tmp_tmp = ft_change_var_environnement(tmp[x],&env, data);
                tmp[x] = tmp_tmp;

            }
            save = ft_strjoin(save_tmp, tmp[x]);
            free(save_tmp);
            save_tmp = ft_strjoin(save, " ");
            free(save);
        }
		// if(tmp_tmp[0]!='\0')
		free(tmp[x]);
		x++;
        // printf("savMIDDLE|%s|\n", save_tmp);

	}

	free((*str));
	// free(tmp_tmp);
	free(tmp[x]);
	free(tmp);
	// free(save);
        // printf("saveEND|%s|\n", save_tmp);

	return(save_tmp);
	// print_char_array_d(tmp);

}

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        signal_recu = sig;
        ft_putstr_fd("^C\n", 2);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}
int ft_search_inputs(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
            {
                if (str[i] != ' ' && str[i] != '\'')
                    return 1;
                i++;
            }
            if (str[i] == '\'')
                i++; // Passe le guillemet simple de fermeture
        }
        else if (str[i] == '"')
        {
            i++;
            while (str[i] && str[i] != '"')
            {
                if (str[i] != ' ')
                    return 1;
                i++;
            }
            if (str[i] == '"')
                i++; // Passe le guillemet double de fermeture
        }
        else if (str[i] != ' ')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int shell_loop(t_node *list, t_data *data, t_env **env)
{
    char *input;

    // Configuration du gestionnaire de signaux

    while (1)
    {    
        signal_recu = 0;   
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, signal_handler);

        input = readline("minishell$ ");

        if (signal_recu == SIGINT)
            data->exit_code = 130;
        if (input == NULL)  // Gestion de Ctrl+D (EOF)
        {
            printf("\nexit\n");
            break;
        }
        if (ft_search_inputs(input) == 0)
        {
            free(input);
            continue;
        }
        ft_init_data(data);
        add_history(input);  // Ajout de la commande à l'historique
        // printf("Je suis input\n|%s|\n", input);
        input = ft_change_input(&input, *env, data);//Il faudra le refaire a la suite 
        // printf("New_input\n|%s|\n", input);
        if (ft_strlen(input) == 0 || ft_white_space(input) == 0)
        {
            //printf("\nICIC\n");
            free(input);
            continue;
        }


        if (ft_parsing(list, data, input, *env) == 1)
        {
            free(input);
            break;
        }

        free(input);
        lexer(list);
        // print_list(list);
        if (lexer_cmd(list, data) == 0)
            data->exit_code = ft_exceve(list, data, &list->env);
        ft_free_return_loop(list);
        
        // printf("Exitcode|%d|", data->exit_code );
    }

    ft_free_end(list, env);
    return data->exit_code;

}
void 	ft_free_return_loop(t_node *list)
{
		free_node(list->next);
		list->next = NULL;
		ft_free_arg(list->arg);
		ft_free_cmd(list->cmd);
		list->arg = NULL;
		list->cmd = NULL;
		list->pipe[0] = -1;

}

void    ft_free_env(t_env **env)
{
    t_env *envt;
    while(*env)
    {
            envt = (*env)->next;
            free((*env)->key);
            free((*env)->value);
            // printf("freeing ptr %p\n", *env);
            free(*env);
            *env = envt;
    }
}

void ft_free_end(t_node *list, t_env **env)
{
        // if(list->save[0] >= 0) close(list->save[0]);
        // if(list->save[1] >= 0) close(list->save[1]);
        ft_free_env(env);
        free(list);
        clear_history();
}

void add_env_to_list(t_env **head, t_env **current, t_env *new_env)
{
	if (*head == NULL)
	{
		*head = new_env;
		*current = new_env;
	}
	else
	{
		(*current)->next = new_env;
		*current = new_env;
	}

}


t_env *ft_insert_env(char **envp)
{
        int i;
        t_env *head = NULL;
        t_env *current = NULL;
        char    *sep;

        i = 0;
        while (envp[i])
        {
                t_env *new_env = (t_env *)malloc(sizeof(t_env));
                sep = strchr(envp[i], '=');
                // printf("sep: (%s) %s\n", envp[i], sep);
                if (sep == NULL)
                    new_env->value = NULL;
                else
                {
                    *sep = '\0';
                    new_env->value = ft_strdup(sep + 1);
                }
				// printf("allocating ptr %p\n", new_env);
                new_env->key = ft_strdup(envp[i]);
                if (sep)
                    *sep = '=';
                // printf("%s => \n\n%s\n\n\n\n\n\n", new_env->key, new_env->value);
                new_env->next = NULL;
                add_env_to_list(&head, &current, new_env);
                i++;
        }
        return (head);
}
int main(int argc, char **argv, char **envp)
{
	t_data data;
	t_node *list;
	(void)argv;
	(void)argc;

    rl_catch_signals = 0;
    data.exit_code = 0;
	if (argc == 2)
		ft_out_exit(1);
	if (!envp || !*envp)
		ft_out_exit(2);
	list = ft_calloc(1, sizeof(t_node));
	if (list == NULL)
		ft_out_exit(3);
	// list->save[0] = dup(STDIN_FILENO);
	// list->save[1] = dup(STDOUT_FILENO);
	list->pipe[0] = -1;
	list->env = ft_insert_env(envp);
	//print_env(list->env);
	organisation_shell_loop(list, &data);

	return (0); // Il faut l'exit code.
}
