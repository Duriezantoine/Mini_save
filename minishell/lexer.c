#include "minishell.h"

static void    set_spec(t_arg *elem);
static void    set_file(t_arg *elem);
static void    set_cmd(t_arg *elem);
static void    set_arg(t_arg *elem);

void print_cmd(t_node *list) {
    if (list == NULL || list->cmd == NULL) {
        printf("List or cmd is NULL\n");
        return;
    }

    printf("Command: %s\n", list->cmd->cmd_and_args[0]);
    for (int i = 1; list->cmd->cmd_and_args[i] != NULL; i++) {
        printf("Argument %d: %s\n", i, list->cmd->cmd_and_args[i]);
    }
}

void print_liste(t_arg *list) {
    t_arg *current = list;
    while (current != NULL) {
        printf("Command: %s, Type: %d\n", current->str_command, current->type);
        current = current->next;
    }
}

int     ft_search_arg(t_arg *list)
{
    int x;

    x = 0;
    while(list)
    {
        if(list->type == CMD || list->type == ARG)
            x++;
        list = list->next;        
    }
    return (x);
}

void    ft_init_cmd(t_cmd **list)
{
    //IL faut initialiser toutes les variables a NULL
    (*list) = malloc(sizeof(t_cmd));
    (*list)->cmd_and_args = NULL;
	(*list)->input = -1;
	(*list)->output = -1;
	(*list)->is_builtin = -1;
	(*list)->prev= NULL;    
	(*list)->next= NULL;

}
void ft_insert_double_tab(t_node *list)
{    
    int count_arg;

    count_arg = ft_search_arg(list->arg);//Commencer l'initialisation du double tableau d'arguments
    list->cmd->cmd_and_args = malloc((count_arg * sizeof(char *)+1));
    count_arg = 0;
    while(list->arg)
    {
        if (list->arg->type == CMD || list->arg->type == ARG)
        {
           list->cmd->cmd_and_args [count_arg] = ft_strdup(list->arg->str_command);
            // printf("\nSAVE = |%s|COUNT_TAB|%d|\n",  list->cmd->cmd_and_args[count_arg], count_arg);
            count_arg++;
        }
        list->arg = list->arg->next;
    }
    list->cmd->cmd_and_args [count_arg]= NULL;
}
// void    ft_insert_infile(t_node *list)
// {

// }

void    ft_intro_cmd(t_node *list)
{
    //Il faut initialiser chaque variables
    //Commencer par la varible 	char **cmd_and_args;
    ft_insert_double_tab(list);//it's ok
    // ft_insert_infile(list);
    print_cmd(list);
}

void    lexer_cmd(t_node *list)//Cette fonction permet d'implementer list->cmd
{
    //verification acces list->arg//Start with list->arglist->cmd = 
    //while(list)
    //{
    ft_init_cmd(&list->cmd);//it's ok
    ft_intro_cmd(list);
    print_liste(list->arg);
    //}
}

void lexer(t_node *list)
{
    while(list)
    {
        set_spec(list->arg);
        set_file(list->arg);
        set_cmd(list->arg);
        set_arg(list->arg);
        // print_liste(list->arg);
        list = list->next;
    }
}

static void    set_spec(t_arg *elem)// sets redirection and pipes

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

static void    set_file(t_arg *elem)// sets infiles and outfiles

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

static void    set_cmd(t_arg *elem)// sets commands

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
static void    set_arg(t_arg *elem)// sets arguments and options

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