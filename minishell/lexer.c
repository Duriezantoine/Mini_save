#include "minishell.h"

static void    set_spec(t_arg *elem);
static void    set_file(t_arg *elem);
static void    set_cmd(t_arg *elem);
static void    set_arg(t_arg *elem);


void print_liste(t_arg *list) {
    t_arg *current = list;
    while (current != NULL) {
        printf("Command: %s, Type: %d\n", current->str_command, current->type);
        current = current->next;
    }
}
void lexer(t_node *list)
{
    while(list)
    {
        set_spec(list->arg);
        set_file(list->arg);
        set_cmd(list->arg);
        set_arg(list->arg);
        printf("\nxx\n");
        print_liste(list->arg);
        list = list->next;
    }
}

// sets redirection and pipes
static void    set_spec(t_arg *elem)
{
    while (elem)
    {
        if (ft_strcmp(elem->str_command, "<<") == 0)
            elem->type = HEREDOC;
        else if (ft_strcmp(elem->str_command, "<") == 0)
            elem->type = INPUT;
        else if (ft_strcmp(elem->str_command, ">>") == 0)
            elem->type = APPEND;
        else if (ft_strcmp(elem->str_command, ">") == 0)
            elem->type = OUTPUT;
        elem = elem->next;
    }
}

// sets infiles and outfiles
static void    set_file(t_arg *elem)
{
    while (elem)
    {
        if (elem->prev && elem->prev->type == INPUT)
            elem->type = INFILE;
        else if (elem->prev && elem->prev->type == OUTPUT)
            elem->type = OUTFILE;
        else if (elem->prev && elem->prev->type == APPEND)
            elem->type = OUTFILE;
        else if (elem->prev && elem->prev->type == HEREDOC)
            elem->type = DELIM;
        elem = elem->next;
    }
}

// sets commands
static void    set_cmd(t_arg *elem)
{
    while (elem && elem->next)
        elem = elem->next;
    while (elem)
    {
        if (elem->type == -1 && (!elem->prev || elem->prev->type >= 0))
        {   
            elem->type = CMD;
        }
        elem = elem->prev;
    }
}

// sets arguments and options
static void    set_arg(t_arg *elem)
{
    t_arg    *tmp;
    int        cmd_count;

    tmp = elem;
    while (tmp)
    {
        if (tmp->type == -1 && tmp->str_command[0] == '-')
            tmp->type = OPTION;
        else if (tmp->type == -1 && tmp->str_command[0] != '-')
            tmp->type = ARG;
        tmp = tmp->next;
    }
    cmd_count = 0;
    while (elem)
    {
        if (elem->type == PIPE)
            cmd_count = 0;
        if (elem->type == CMD)
            cmd_count++;
        if (elem->type == CMD && cmd_count > 1)
            elem->type = ARG;
        elem = elem->next;
    }
}
