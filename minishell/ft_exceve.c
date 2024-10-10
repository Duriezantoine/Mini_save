/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exceve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aduriez <aduriez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 11:35:23 by aduriez           #+#    #+#             */
/*   Updated: 2024/10/10 02:46:52 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

struct s_exec {
        char *exec;
        char **argv;
        char **envp;
        int in;
        int out;
        int pid;
};

int lst_len(t_node *list) {
        int ret = 0;
        while(list) {
                ret++;
                list = list->next;
        }
        return ret;
}

struct s_exec *lst_to_execs(t_node *list, int *len) {
        *len = lst_len(list);
        struct s_exec *ret = ft_calloc((size_t)len, sizeof(struct s_exec));
        if(!ret) return NULL;
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

int ft_wait_all(struct s_exec *execs, size_t len) {
      int i;
      int ret;

      ret = 0;
      i = 0;
      while(i < len) {
              waitpid(execs[i].pid, &ret, 0);
              i++;
      }
      return WEXITSTATUS(ret);
}

void free_exec(struct s_exec e) {
        free(e.exec);
        int i = 0;
        while(e.argv[i]) {
                free(e.argv[i]);
                i++;
        }
        i = 0;
        while(e.envp[i]) {
                free(e.argv[i]);
                i++;
        }
        if(e.in > 2) close(e.in);
        if(e.out > 2) close(e.out);
}

int cdt_len(char **a) {
        if(!a) return 0;
        int i = 0;
        while(a[i]) {
                i++;
        }
        return i;
}

void free_all_exec(struct s_exec *execs, int len) {
        int i;
        i = 0;
        while(i < len) {
                free_exec(execs[i]);
                i++;
        }
}

struct s_exec dup_exec(struct s_exec e) {
        struct s_exec ret;
        ret.exec = ft_strdup(e.exec);
        ret.argv = ft_calloc(cdt_len(e.argv), sizeof(char *));
        ret.envp = ft_calloc(cdt_len(e.envp), sizeof(char *));
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

void builtin(char *name, char **argv, char **envp) {
        int founded = 0;
        if(streq(name, "env")) {
                founded = 1;
                buil
        }
}

void exec(char *name, char **argv, char **envp) {
        builtin(name, argv, envp);
        execve(name, argv, envp);
}

void ft_exec(struct s_exec *execs, int idx, int len) {
        struct s_exec self = dup_exec(execs[idx]);
        dup2(self.in, 0);
        dup2(self.out, 1);
        free_all_exec(execs, len);
        int argcl
        exec(self.exec, self.argv, self.envp);
}

int    ft_exceve(t_node *list, t_data *data, t_env **env)
{
        int len;
        struct s_exec *lst = lst_to_execs(list, &len);
        int last_in = 0;
        int p[2];
        int i = 0;
        while(i < len - 1) {
                if(pipe(p) < 0) {
                        printf("WARNING: pipe syscall broke [some commands might not work as excpected]\n");
                        break;
                }
                if(lst[i].in < 0) lst[i].in = last_in;
                if(lst[i].out < 0) lst[i].out = p[1];
                if(last_in > 0) close(last_in);
                if(p[1] >= 0) close(p[1]);
                last_in = p[0];
                ft_fork(255, ft_exec, lst, (struct s_ituple){i, len});
                i++;
        }
        if(lst[i].in < 0) lst[i].in = last_in;
        if(lst[i].out <= 0) lst[i].out = 1;
        ft_fork(255, ft_exec, lst, (struct s_ituple){i, len});
        if(last_in > 0) close(last_in);
        int ret = ft_wait_all(lst, len);
        i = 0;
        while(i < len) {
                free_exec(lst[i]);
                i++;
        }
        return ret;
}
