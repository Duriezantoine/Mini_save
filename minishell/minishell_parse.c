/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/14 17:29:23 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	shell_loop(list, &data, &list->env);
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
void print_env_list(t_env *env) {
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
    char **result = (char **)malloc(sizeof(char *) * len);
    if (!result)
        return NULL;
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

	count = 0;
	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (!is_quote(str[i], &in_single, &in_double))
		{
			if (str[i] == '$' && !in_single && !in_double)
				count++;
		}
		i++;
	}
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

void	ft_change_input(char **str, t_env *env)
{
	char *tmp_tmp;
	char **tmp;
	char *save;
	char *save_tmp;
	int x;
	x = 0;
	(*str) = ft_strjoin((*str), " ");
	while (count_dollars_outside_quotes((*str))<=0)
		break;	
	save = ft_copy_start((*str), '$');
	// save = ft_strjoin(str, '$');
	save_tmp = ft_strdup(" ");
	tmp = ft_split_d((*str));
	while(tmp[x])
	{
		if (ft_space_or_null(tmp[x])==0)
			break;
		if (tmp[x][0]== '$')
		{
			tmp_tmp = ft_change_var_environnement(tmp[x],&env);
			tmp[x] = ft_strdup(tmp_tmp);

		}
		save_tmp = ft_strjoin(save_tmp, tmp[x]);
		save_tmp = ft_strjoin(save_tmp, " ");
		// if(tmp_tmp[0]!='\0')
		// 	free(tmp_tmp);
		// free(tmp[x]);
		x++;
		if (tmp[x]== NULL)
			break;
	}
	free((*str));
	printf("New input = %s",save_tmp);
	(*str) = ft_strdup(save_tmp);
	//print_char_array_d(tmp);
	//free(save_tmp)

}

int shell_loop(t_node *list, t_data **data, t_env **env)
{
	char *input;
	(void)data;
	(void)env;
	int exitcode;
	while (signal_recu != SIGKILL)
	{    

		ft_init_data(&data, list);
		input = readline("minishell$ ");
		ft_change_input(&input, *env);
		printf("INPUT|%s|", input);
		//Faire une conditions ici pour le dollar 
		if ((!input || ft_strlen(input)) && ft_white_space(input) == 0)
			ft_out_exit(1);
		// Mise en place d'une structure pour les signaux *2
		if (ft_parsing(list, data, input, *env) == 1)
		{
            free(input);
			break;
		} // Mise en place d'une structure
		free(input);
		lexer(list);//celui la est bon 
		lexer_cmd(list, *data);//Here__cod present ici dans le parsing

		exitcode = ft_exceve(list, *data, &list->env);
		ft_free_return_loop(list, *data);
		// print_env_list(list->env);

	}
	ft_free_end(list, env);
	exit(exitcode);
	return (0);
}
void 	ft_free_return_loop(t_node *list, t_data *data)
{
		free_node(list->next, data);
		list->next = NULL;
		ft_free_arg(list->arg);
		ft_free_cmd(list->cmd);
		list->arg = NULL;
		list->cmd = NULL;
		list->pipe[0] = -1;

}

void ft_free_end(t_node *list, t_env **env)
{
        if(list->save[0] >= 0) close(list->save[0]);
        if(list->save[1] >= 0) close(list->save[1]);
        t_env *envt;
        while(*env) {
                envt = (*env)->next;
                free((*env)->key);
                free((*env)->value);
				// printf("freeing ptr %p\n", *env);
                free(*env);
                *env = envt;
        }
        free(list);
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

        i = 0;
        while (envp[i])
        {
                t_env *new_env = (t_env *)malloc(sizeof(t_env));
				// printf("allocating ptr %p\n", new_env);
                new_env->key = ft_copy_start(envp[i], '=');
                new_env->value = ft_copy_end(envp[i], '=');
                // printf("%s => \n\n%s\n\n\n\n\n\n", new_env->key, new_env->value);
                new_env->next = NULL;
                add_env_to_list(&head, &current, new_env);
                i++;
        }
        return (head);
}
int main(int argc, char **argv, char **envp)
{
	t_data *data = 	NULL;
	t_node *list;
	(void)argv;
	(void)argc;

	if (argc == 2)
		ft_out_exit(1);
	if (!envp || !*envp)
		ft_out_exit(2);
	list = ft_calloc(1, sizeof(t_node));
	if (list == NULL)
		ft_out_exit(3);
	list->save[0] = dup(STDIN_FILENO);
	list->save[1] = dup(STDOUT_FILENO);
	list->pipe[0] = -1;
	list->env = ft_insert_env(envp);
	//print_env(list->env);
	organisation_shell_loop(list, data);

	return (0); // Il faut l'exit code.
}
