/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/12 12:29:09 by aduriez          ###   ########.fr       */
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
        printf("%s ", *argv);
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
        free_split(split_path);
        return NULL;
}

struct s_exec *lst_to_execs(t_node *list, int *len) {
        *len = lst_len(list);
        struct s_exec *ret = ft_calloc(*len, sizeof(struct s_exec)); // Correction: Suppression du cast (size_t)
        if(!ret) return NULL;
        char **env = get_env_cdt(list->env);
        int i = 0;
        while(list) {
                ret[i].exec = get_program_name(list->cmd->cmd_and_args[0], list->cmd->is_builtin);
                ret[i].argv = clone_cdt(list->cmd->cmd_and_args);
                ret[i].envp = clone_cdt(env);
                ret[i].in = list->cmd->input;
                ret[i].out = list->cmd->output;
                ret[i].pid = -1;
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
            return EXIT_FAILURE;
        }
        if (WIFEXITED(status)) {
            last_exit_status = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            fprintf(stderr, "Command terminated by signal %d\n", WTERMSIG(status));
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
        return founded;
}

void exec(char *name, char **argv, char **envp) {
        if(!builtin(name, argv, envp))
        {    
                
                // Imprimer name
                //printf("name: %s\n", name);
                name = get_path(name);
                // Imprimer argv
                //printf("argv: ");
                //print_args(argv);

                // Imprimer envp
                //printf("envp:\n");
                //print_env(envp);
                
                execve(name, argv, envp);
        }
        else    
        {
                bulting_echo(argv, 0);
                return;
        }
}

void ft_exec(struct s_exec *execs, int idx, int len) {
        struct s_exec self = dup_exec(execs[idx]);
        dup2(self.in, 0);
        dup2(self.out, 1);
        free_all_exec(execs, len);
        exec(self.exec, self.argv, self.envp);
        free_exec(self);
}

int ft_exceve(t_node *list, t_data *data, t_env **env)
{
    int len;
    struct s_exec *lst = lst_to_execs(list, &len);
    int last_in = 0;
    int p[2];
    int i = 0;

    (void)data; // Pour éviter l'avertissement de paramètre non utilisé
    (void)env;  // Pour éviter l'avertissement de paramètre non utilisé

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
            if (i < len - 1) close(p[0]);
            if (lst[i].in != 0) {
                dup2(lst[i].in, 0);
                close(lst[i].in);
            }
            if (lst[i].out != 1) {
                dup2(lst[i].out, 1);
                close(lst[i].out);
            }
            exec(lst[i].exec, lst[i].argv, lst[i].envp);
            exit(1);  // En cas d'échec de exec
        }

        // Code du processus parent
        if (last_in > 0) close(last_in);
        if (i < len - 1) {
            close(p[1]);
            last_in = p[0];
        }

        i++;
    }

    int ret = ft_wait_all(lst, len);
    free_all_exec(lst, len);
    exit(ret);
    return ret;
}