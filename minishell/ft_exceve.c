/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/14 17:42:04 by aduriez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

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
        full_path = ft_strjoin(split_path[i], "/");
        full_path = ft_strjoin(full_path, str);

        if (access(full_path, F_OK | X_OK) != -1)
        {
        //     printf("Chemin trouvé: %s\n", full_path);
            // free_split(split_path);
        //     printf("Chemin non trouvé pour: %s\n", str);
            return(full_path);
        }

        free(full_path);
        i++;
    }
//     printf("\nCommand not valid\n");
    return(str);
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
        if(!ret) return NULL;
        int i = 0;
        while(env) {
                ret[i] = ft_calloc(ft_strlen(env->key) + ft_strlen(env->value) + 2, sizeof(char));
                if(!ret[i]) {
                        int j = 0;
                        while(j < i) {
                                free(ret[j]);
                                j++;
                        }
                        free(ret); // Correction: Libération de ret
                        return NULL;
                }
                real_strcat(ret[i], env->key);
                ret[i][ft_strlen(env->key)] = '='; // Correction: Ajout direct du caractère '='
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

int builtin(char *name, char **argv, char **envp) {
        (void)argv;
        (void)envp;
        int founded = 0;
        if(strequ(name, "env")) {
                printf("env\n");
                founded = 1;
        }
                if(strequ(name, "echo")) {
                // printf("env\n");
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
        return founded;
}

int exec(char *name, char **argv, char ***envp, struct s_exec **lst, t_env *env) {
        int i;
        (void)env;
        i = 0;
        int built;
       built = builtin(name, argv, (*envp) );
        if(!builtin(name, argv, (*envp) ))
        {                   // Imprimer name
                name = get_path(name);
                // Imprimer argv
                //printf("argv: ");
                //print_args(argv);
              //  printf("Command \'%s\' not found\n", name);

                // Imprimer envp
                //printf("envp:\n");
                //print_env(envp);
                
                execve(name, argv, (*envp));
                fprintf(stderr, "Command '%s' not found\n", name);
                return(0);
        }
        else if(built==1)
        {

        }
       else if (built == 2) 
        {
                // printf("Je susi bulting echo");
                bulting_echo(argv,1);
                return(0);
        }
         else if (built == 3) 
        {
               bulting_export(argv, envp);
               while((*lst[i]->envp))
               {
                        (*lst)[i].envp= (*envp);
                        i++;
               }      
        }
//        print_env((*envp));
        return(0);
}
int ft_excev_butlin(struct s_exec **lst, t_node **list)
{        int i;
        i = 0;
        int built;
       built = builtin(lst[0]->exec,lst[0]->argv, lst[0]->envp) ;
                if (built == 1) 
        {
                printf("Je susi bulting Env");
               bulting_env((*list)->cmd,(*list));
 
        }   
        if (built == 2) 
        {
                printf("\nJe susi bulting echo\n");
                bulting_echo(lst[0]->argv,1);
                return(0);
        }
         if (built == 3) 
        {
                printf("Je susi bulting Export");
                 print_args(lst[0]->argv);
               bulting_export(lst[0]->argv, &lst[0]->envp);
 
        }         
        if (built == 4) 
        {
                printf("Je susi bulting Cd");
               bulting_cd((*list)->cmd,(*list),  &(*list)->env);
 
        }
        if (built == 5) 
        {
                printf("Je susi bulting Unset");
               bulting_unset( &lst[0]->envp,(*list)->cmd,(*list));
                 //Penser a free ici;
                 lst[0]->envp=get_env_cdt((*list)->env);
                
        }
        if (built == 6) 
        {
                printf("Je susi bulting Pwd");
                bulting_pwd();
        }
        

        (*list)->env = ft_insert_env(lst[0]->envp);
        // print_env_list((*list)->env);
        return(0);
}

int ft_exceve(t_node *list, t_data *data, t_env **env)
{
    int len;
    struct s_exec *lst = lst_to_execs(list, &len);
    int last_in = 0;
    int p[2];
    int error_pipe[2];
    int i = 0;
    int ret = -1;
    (void)data;
    (void)env;

    if (pipe(error_pipe) < 0) {
        fprintf(stderr, "Erreur: Échec de la création du pipe d'erreur.\n");
        return -1;
    }

    if (len == 1 && ft_exceve_bulting(list->cmd->cmd_and_args[0]) == 0)
    {
        close(error_pipe[0]);
        close(error_pipe[1]);
        return ft_excev_butlin(&lst, &list);
    }

    while (i < len) {
        if (i < len - 1) {
            if (pipe(p) < 0) {
                fprintf(stderr, "Erreur: Échec de la création du pipe.\n");
                break;
            }
        }
        if (lst[i].in < 0) lst[i].in = last_in;
        if (lst[i].out < 0) lst[i].out = (i < len - 1) ? p[1] : 1;

        lst[i].pid = fork();
        if (lst[i].pid < 0) {
            fprintf(stderr, "Erreur: Échec du fork.\n");
            break;
        } else if (lst[i].pid == 0) {
            // Code du processus enfant
            close(error_pipe[0]);
            if (i < len - 1) close(p[0]);
            if (lst[i].in != 0) {
                dup2(lst[i].in, 0);
                close(lst[i].in);
            }
            if (lst[i].out != 1) {
                dup2(lst[i].out, 1);
                close(lst[i].out);
            }
            dup2(error_pipe[1], 2);  // Rediriger stderr vers le pipe d'erreur
            close(error_pipe[1]);
            
            exit(exec(lst[i].exec, lst[i].argv, &lst[i].envp, &lst, list->env));
        }

        // Code du processus parent
        if (last_in > 0) close(last_in);
        if (i < len - 1) {
            close(p[1]);
            last_in = p[0];
        }
        i++;
    }

    close(error_pipe[1]);  // Fermer l'extrémité d'écriture du pipe d'erreur

    ret = ft_wait_all(lst, len);

    // Lire et afficher les erreurs après l'exécution de toutes les commandes
    char error_buffer[1024];
    ssize_t error_read;
    while ((error_read = read(error_pipe[0], error_buffer, sizeof(error_buffer))) > 0) {
        write(2, error_buffer, error_read);
    }
    close(error_pipe[0]);

    list->env = ft_insert_env(lst[0].envp);
    free_all_exec(lst, len);
    return ret;
}
