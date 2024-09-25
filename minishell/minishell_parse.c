/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:08:04 by dpoltura          #+#    #+#             */
/*   Updated: 2024/06/29 17:24:46 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void organisation_shell_loop(t_node *list, t_data **data, char **env)
{
	(void)list;
	// Declaration des signaux
	shell_loop(list, data, env);
	// free la command_line
}

int shell_loop(t_node *list, t_data **data, char **env)
{
	char *input;
	(void)env;
	(void)data;

	while (1)
	{
		// Creation de l'input
		input = readline("minishell$ ");
		if (!input)
			ft_out_exit(1);
		// Mise en place d'une structure pour les signaux *2
		if (ft_parsing(list, data, input) == 1)
		{
			// Il faut changer le return
			return (1);
		} // Mise en place d'une structure
		lexer(list);
		// Libérer l'input après utilisation
		free(input);
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_data *data;
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
	ft_init_data(&data, list);
	organisation_shell_loop(list, &data, envp);
	return (0); // Il faut l'exit code.
}
