#include "minishell.h"

static void set_spec(t_arg *elem);
static void set_file(t_arg *elem);
static void set_cmd(t_arg *elem);
static void set_arg(t_arg *elem);

void write_to_temp_file(int fd, char *buffer)
{
    write(fd, buffer, strlen(buffer));
}

int ft_search_arg(t_arg *list)
{
    int x;

    x = 0;
    while (list)
    {
        if (list->type == CMD || list->type == ARG)
            x++;
        list = list->next;
    }
    return (x);
}

void ft_init_cmd(t_cmd **list)
{
    // IL faut initialiser toutes les variables a NULL
    (*list) = malloc(sizeof(t_cmd));
    (*list)->cmd_and_args = NULL;
    (*list)->input = -1;
    (*list)->output = -1;
    (*list)->is_builtin = -1;
    (*list)->prev = NULL;
    (*list)->next = NULL;
}
void ft_insert_double_tab(t_cmd **list, t_arg *list_arg)
{
    t_arg *args = list_arg;
    int count_arg;
    count_arg = ft_search_arg(list_arg); // Commencer l'initialisation du double tableau d'arguments
    (*list)->cmd_and_args = malloc((count_arg * sizeof(char *) + 1));
    count_arg = 0;
    while (args)
    {
        if (args->type == CMD || args->type == ARG)
        {
            (*list)->cmd_and_args[count_arg] = ft_strdup(args->str_command);
            // printf("\nSAVE = |%s|COUNT_TAB|%d|\n",  (*list)->cmd_and_args[count_arg], count_arg);
            count_arg++;
        }
        args = args->next;
    }
    (*list)->cmd_and_args[count_arg] = NULL;
}



void ft_insert_cmd_here_doc(t_node *list, t_cmd **list_cmd, t_arg *list_arg, t_data *data) // Il faut voir
{

    (void)data;
    (void)list_cmd;
    t_arg *current = list_arg;
    while (current)
    {
        if (current->type == HEREDOC && current->next->type == DELIM ) // Ce qui permet de ne pas creer d'infile car il n'y a pas de commande
        {
            current = current->next;
            printf("\nNBR_CMD = %d\n", (*list_cmd)->cmd);
            ft_here_doc(data, list, &list->env, current->str_command);
        }
        current = current->next;
    }
}

void ft_verif_cmd(t_cmd **list, t_arg *list_arg)
{
    t_arg *arg = list_arg;
    ;
    int count;

    count = 0;

    while (arg)
    {
        if (arg->type == CMD)
        {
            printf("Je suis la cmd |%s|", arg->str_command);
            count++;
        }
        arg = arg->next;
    }

    (*list)->cmd = count;
}

void lexer_cmd(t_node *list, t_data *data) // Cette fonction permet d'implementer list->cmd
{
    (void)data;
    // verification acces list->arg//Start with list->arglist->cmd =
    while (list)
    {
        ft_init_cmd(&list->cmd);                     // it's ok
        ft_insert_double_tab(&list->cmd, list->arg); // it's ok
        ft_verif_cmd(&list->cmd, list->arg);
        ft_insert_cmd_here_doc(list, &list->cmd, list->arg, data);
        // Il faut ensuite verifier tous les infiles et les outfiles
        data->count = data->count + 1;
        list = list->next;
    }
    // IL faut maintenat voir si il y a here_doc et le placer en premeir
}

void lexer(t_node *list)
{
    while (list)
    {
        set_spec(list->arg);
        set_file(list->arg);
        set_cmd(list->arg);
        set_arg(list->arg);
        list = list->next;
        printf("\nXXX\n");
    }
}

static void set_spec(t_arg *elem) // sets redirection and pipes

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

static void set_file(t_arg *elem) // sets infiles and outfiles

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

static void set_cmd(t_arg *elem) // sets commands

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
static void set_arg(t_arg *elem) // sets arguments and options

{
    t_arg *tmp;
    int cmd_count;

    tmp = elem;
    while (tmp)
    {
        if (tmp->type == -1 && tmp->str_command[0] == '-')
            tmp->type = ARG;
        else if (tmp->type == -1 && tmp->str_command[0] != '-')
            tmp->type = ARG;
        tmp = tmp->next;
    }
    cmd_count = 0;
    while (elem)
    {
        if (elem->type == CMD)
            cmd_count++;
        if (elem->type == CMD && cmd_count > 1)
            elem->type = ARG;
        elem = elem->next;
    }
}
