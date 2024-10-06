/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/10/03 15:56:07 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(void)list;
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


int shell_loop(t_node *list, t_data **data, t_env **env)
{
	char *input;
	(void)data;
	(void)env;
	while (1)
	{    
		//print_environment(*env);
		//printf("\n\n\n\n\n\n\n");
		//print_directory_contents();//Permet de verifier dans qu'elle repertoire je suis.
		// print_env(list->env);//Permet de verifier si l'environnement a bien ete modifier 
		//printf("\nminishell\n");
		ft_init_data(&data, list);

		// Creation de l'input
		input = readline("minishell$ ");
		if (!input)
			ft_out_exit(1);
		
		// if((*data) == NULL)
		// {
		// 	printf("data_echo vide");
		// 	return(1);
		// }
		// Mise en place d'une structure pour les signaux *2
		if (ft_parsing(list, data, input) == 1)
		{
			// Il faut changer le return
			return (1);
		} // Mise en place d'une structure
		lexer(list);//celui la est bon 
		lexer_cmd(list, *data);//Here__cod present ici dans le parsing
		// print_arg_arg(list->arg);//Permet de verifier toutes les argument du noeuds 
		t_node *tmp = list;
		print_all_cmds(tmp);//Permet de verifier toutes les commandes 
		ft_exceve(list, *data, &list->env);
		free_node(list, *data);
		// Libérer l'input après utilisation

		free(input);
	}
	return (0);
}
// void init_env_node(t_env *new_env, char **tmp, char *envp_i)
// {
// 	new_env->key = strdup(tmp[0]);
// 	new_env->value = (char **)malloc(sizeof(char *) * (strlen(envp_i) + 1));
// 	if (new_env->value == NULL)
// 	{
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	int j = 0;
// 	for (int k = 1; tmp[k] != NULL; k++)
// 	{
// 		new_env->value[j] = strdup(tmp[k]);
// 		j++;
// 	}
// 	new_env->value[j] = NULL;
// }

void add_env_to_list(t_env **head, t_env **current, t_env *new_env, char *envp_i)
{
	(void)envp_i;
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
	char **tmp;
	t_env *head = NULL;
	t_env *current = NULL;
	int x;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split((const char *)envp[i], '=');
		
		t_env *new_env = (t_env *)malloc(sizeof(t_env));
		new_env->key  = ft_strdup(tmp[0]);
        new_env->value = ft_strdup(tmp[1]);

        // Concatenate the values if there are more than one
        x = 2;
        while (tmp[x]) {
            char *temp = new_env->value;
            new_env->value = ft_strjoin(new_env->value, tmp[x]);
            free(temp);
            x++;
        }

		new_env->next = NULL;
		add_env_to_list(&head, &current, new_env, envp[i]);
		i++;
		free(tmp);
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
	{
		ft_putstr_fd("Error arguments", 2);
		exit(2);
	}
	if (!envp || !*envp)
	{
		ft_putstr_fd("No environment", 2);
		exit(1);
	}
	list = malloc(sizeof(t_node));
	if (list == NULL)
	{
		fprintf(stderr, "Memory allocation failed for data\n");
		exit(1);
	}
	ft_init_env(&list->env);
	list->env = ft_insert_env(envp);
	//print_env(list->env);
	organisation_shell_loop(list, data);
	return (0); // Il faut l'exit code.
}
