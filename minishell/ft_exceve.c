/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/10 13:02:00 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

/////////////////////////////////////////////Fonction pour changer le list-env en char **//////////////////////////////////////////////////////////////////////////////////////////////////////////


// Fonction pour concaténer key et value avec un '=' entre eux
char *concat_key_value(const char *key, const char *value)
{
    size_t key_len = strlen(key);
    size_t value_len = strlen(value);
    char *result = malloc(key_len + value_len + 2); // +2 pour '=' et '\0'
    if (!result)
        return NULL;

    strcpy(result, key);
    strcat(result, "=");
    strcat(result, value);
    return result;
}

int count_env_list(t_env *env)
{
    int count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return count;
}


// Fonction pour convertir la liste chaînée en char **
char **env_list_to_array(t_env *env)
{
    int count = count_env_list(env);
    char **array = malloc((count + 1) * sizeof(char * )); // +1 pour le NULL final
    if (!array)
        return NULL;

    int i = 0;
    t_env *current = env;
    while (current)
    {
        array[i] = concat_key_value(current->key, current->value);
        if (!array[i])
        {
            // Libérer la mémoire allouée en cas d'échec
            for (int j = 0; j < i; j++)
                free(array[j]);
            free(array);
            return NULL;
        }
        current = current->next;
        i++;
    }
    array[i] = NULL; // Terminer le tableau avec NULL
    printf("ARRAY|%s|",array[2]);
    return (array);
}

void print_env_array(char **env)
{
    if (!env)
        return;

    for (int i = 0; env[i]; i++)
    {
        printf("%s\n", env[i]);
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Fonction pour changer le list->cmd_cmd_and_args en tableau de double//////////////////////////////////////////////////////////////////////////////////////////////////////////

int ft_count_arg(t_cmd *cmd)
{
        char **tmp;
        int i;

        i = 0;
        tmp = cmd->cmd_and_args;
        while(tmp[i])
                i++;
        printf("Je suis le nbrarg de cmd[%d]", i);
        return(i);

}

 char  *ft_insert_arg_excve( char **double_table,int x)
 {
        int i;
        i = 0;
        char *str;
        while(double_table[i])
        {
                if (i == x)
                {
                        str = ft_strdup(double_table[i]);
                }
                i++;
        }
        printf("\nVoicisSV |%s|\n", str);
        return(str);
 }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Fonction pour modifier la data pour le double tableau de chaine de caractere//////////////////////////////////////////////////////////////////////////////////////////////////////////
char *get_path(char *str)
{
    char *path;
    char **split_path;
    char *full_path;
    int i;

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
        full_path = ft_strjoin(split_path[i], "/");
        full_path = ft_strjoin(full_path, str);

        if (access(full_path, F_OK | X_OK) != -1)
        {
            printf("Chemin trouvé: %s\n", full_path);
            // free_split(split_path);
            printf("Chemin non trouvé pour: %s\n", str);
            return(full_path);
        }

        free(full_path);
        i++;
    }
    return(str);
    // free_split(split_path);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int strequ(char *s1, char *s2) {
        return strcmp(s1, s2) == 0;
}

struct s_exec {
        char *exec;//it's ok
        char **argv;//it's ok
        char **envp;//it's ok
        int in ;//Ca doit pour 
        int out;
        int pid;
};

int lst_len(t_node *list) {
        int ret = 0;

        while (list) {
                ret++;
                list = list->next;
        }
        printf("Je suis le nbr de commande%d", ret);
        return ret;
}

struct s_exec *lst_to_execs(t_node *list, int *len) {
        *len = lst_len(list);
        struct s_exec *ret = ft_calloc(*len, sizeof(struct s_exec));
        return ret;
}

struct s_ituple {
        int idx;
        int len;
};

int ft_fork(int exit_err, void (*func)(struct s_exec *, int, int), struct s_exec *data, struct s_ituple il) {
        int pid;
                printf("\n4Je passe \n");

        if (!func)
                return -1;
        pid = fork();
        if (pid < 0)
                return -1;
        if (pid == 0) {
                func(data, il.idx, il.len);
                exit(exit_err);
        }
        return pid;
}

int ft_wait_all(struct s_exec *execs, int len) {
        int i;
        int ret;

        ret = 0;
        i = 0;
        while (i < len) {
                waitpid(execs[i].pid, &ret, 0);
                i++;
        }
        return WEXITSTATUS(ret);
}
void free_exec(struct s_exec e) {
        free(e.exec);
        int i = 0;
        while (e.argv && e.argv[i]) {
                free(e.argv[i]);
                i++;
        }
        free(e.argv);
        i = 0;
        printf("1Environnemnt ");
        // while (e.envp && e.envp[i]) {
        //         free(e.envp[i]);
        //         i++;
        // }
        // free(e.envp);
        // if (e.in > 2) close(e.in);
        // if (e.out > 2) close(e.out);
        printf("2Environnemnt ");

}

int cdt_len(char **a) {
        if (!a) return 0;
        int i = 0;
        while (a[i]) {
                i++;
        }
        return i;
}

void free_all_exec(struct s_exec *execs, int len) {
        int i = 0;
        while (i < len) {
                free_exec(execs[i]);
                i++;
        }
        free(execs);
}

struct s_exec dup_exec(struct s_exec e) {
        struct s_exec ret = {0};
        ret.exec = ft_strdup(e.exec);
        if (!ret.exec) return ret;

        int argv_len = cdt_len(e.argv);
        int envp_len = cdt_len(e.envp);
        
        ret.argv = ft_calloc(argv_len + 1, sizeof(char *));
        ret.envp = ft_calloc(envp_len + 1, sizeof(char *));
        
        if (!ret.argv || !ret.envp) {
                free_exec(ret);
                return (struct s_exec){0};
        }

        for (int i = 0; i < argv_len && e.argv[i]; i++) {
                ret.argv[i] = ft_strdup(e.argv[i]);
                if (!ret.argv[i]) {
                        free_exec(ret);
                        return (struct s_exec){0};
                }
        }

        for (int i = 0; i < envp_len && e.envp[i]; i++) {
                ret.envp[i] = ft_strdup(e.envp[i]);
                if (!ret.envp[i]) {
                        free_exec(ret);
                        return (struct s_exec){0};
                }
        }

        ret.in = e.in;
        ret.out = e.out;
        return ret;
}

void builtin(char *name, char **argv, char **envp) {
        (void)argv;
        if (strequ(name, "env")) {
                int i = 0;
                while (envp && envp[i]) {
                        printf("%s\n", envp[i]);
                        i++;
                }
        }
        // Ajoutez d'autres built-ins ici si nécessaire
}

void exec(char *name, char **argv, char **envp) {
        builtin(name, argv, envp);
        execve(name, argv, envp);
}

void ft_exec(struct s_exec *execs, int idx, int len) {
        struct s_exec self = dup_exec(execs[idx]);
        // if (!self.exec)
        // {
        //         printf("\n5Je passe \n");
        //          exit(1);
        // }
        printf("\n6Je passe \n");

        dup2(self.in, 0);
        dup2(self.out, 1);
        
        free_all_exec(execs, len);
        printf("\nJe CMD=|%s|\n",self.exec);
        execve(self.exec, self.argv, self.envp);
        exit(1);
}

void    ft_change_data(t_node *list,struct  s_exec **lst, int len)
{
        int i;
        int count;
        i = 0;
        int x;
        t_node *tmp ;
        tmp = list;
        (*lst)[0].envp = env_list_to_array(list->env);
        printf("\nVALUEQWE|%s|\n", (*lst)[0].envp[2]);

        while(i<len)
        {
                if(i != 0)
                        (*lst)[i].envp= (*lst)[0].envp;
                x = 0;  
                printf("\n1 \n\n");

                count = ft_count_arg(tmp->cmd);
                                printf("\n2 \n\n");

                (*lst)[i].in = tmp->cmd->input;
                                printf("\n3 \n\n");

                (*lst)[i].out= tmp->cmd->output;
                printf("\n4 \n\n");
                (*lst)[i].argv= malloc(sizeof(char *) *(count+1));//Ce qui permet de malloc l'entierte de la chaine de la double chaine de caractere
                printf("\n5 \n\n");

                while(x<count)
                {
                        // printf("\nXXX\n");
                        (*lst)[i].argv[x]=ft_insert_arg_excve( tmp->cmd->cmd_and_args, x); 
                        x++;
                }
                                printf("\n6 \n\n");
                printf("\nPATH= |%s| \n\n",(*lst)[i].exec );
                (*lst)[i].exec =get_path((*lst)[i].argv[0]);
                 printf("\nPATH= |%s| \n\n",(*lst)[i].exec );

                //Il faut aller cherche dans c
                i++;
                tmp = tmp->next;
                printf("\n9 \n\n");

        }
        // free(env);

        printf("\n10 \n\n");

}

int ft_exceve(t_node *list, t_data *data, t_env **env) {
        (void)data;
        (void)env;
        int len;
        struct s_exec *lst = lst_to_execs(list, &len);
        //Verification du changement 
        ft_change_data(list, &lst, len);
        printf("\nVALUEQWE|%s|\n", lst[0].envp[2]);
        if (!lst) return 1;

        int last_in = 0;
        int p[2];
                printf("\n2Je passe \n");

        for (int i = 0; i < len; i++) {
                if (i < len - 1) {
                        if (pipe(p) < 0) {
                                perror("pipe");
                                free_all_exec(lst, len);
                                return 1;
                        }
                }

                if (lst[i].in < 0) lst[i].in = last_in;
                if (i < len - 1) {
                        if (lst[i].out < 0) lst[i].out = p[1];
                } else {
                        if (lst[i].out <= 0) lst[i].out = 1;
                }
                printf("\n3Je passe \n");

                lst[i].pid = ft_fork(255, ft_exec, lst, (struct s_ituple){i, len});
                if (lst[i].pid < 0) {
                        perror("fork");
                        free_all_exec(lst, len);
                        return 1;
                }

                if (last_in > 2) close(last_in);
                if (i < len - 1) {
                        close(p[1]);
                        last_in = p[0];
                }
        }

        if (last_in > 2) close(last_in);
        int ret = ft_wait_all(lst, len);
        free_all_exec(lst, len);
        return ret;
}
