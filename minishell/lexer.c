#include "minishell.h"

static void set_spec(t_arg *elem);
static void set_file(t_arg *elem);
static void set_cmd(t_arg *elem);
static void set_arg(t_arg *elem);

void print_arg(t_arg *arg) {
    if (arg == NULL) {
        printf("t_arg is NULL\n");
        return;
    }
    printf("t_arg:\n");
    printf("  str_command: %s\n", arg->str_command);
    printf("  type: %d\n", arg->type);
    printf("  prev: %p\n", (void *)arg->prev);
    printf("  next: %p\n", (void *)arg->next);
}

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
    (*list)->is_builtin = -1;
    (*list)->prev = NULL;
    (*list)->next = NULL;
    (*list)->input_str = NULL;
    (*list)->output_str = NULL;
}
void ft_insert_double_tab(t_cmd **list, t_arg *list_arg)
{
    t_arg *args = list_arg;
    int count_arg;
    count_arg = ft_search_arg(list_arg); // Commencer l'initialisation du double tableau d'arguments
    (*list)->cmd_and_args = malloc((count_arg + 1) * sizeof(char *));
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


t_arg *find_previous_node(t_arg *head, t_arg *current) {
    t_arg *previous = NULL;
    t_arg *temp = head;

    while (temp != NULL && temp->next != current) {
        previous = temp;
        temp = temp->next;
    }

    return previous;
}

// Fonction pour supprimer un nœud spécifique
void delete_node(t_arg **head, t_arg *node_to_delete) {
    if (*head == NULL || node_to_delete == NULL) {
        // La liste est vide ou le nœud à supprimer est NULL
        return;
    }

    t_arg *previous = find_previous_node(*head, node_to_delete);

    if (previous != NULL) {
        previous->next = node_to_delete->next; // Mettre à jour le pointeur du nœud précédent
    } else {
        *head = node_to_delete->next; // Mettre à jour la tête de la liste
    }

    if (node_to_delete->next != NULL) {
        node_to_delete->next->prev = previous; // Mettre à jour le pointeur précédent du nœud suivant
    }

    free(node_to_delete); // Libérer la mémoire du nœud actuel
}


int ft_insert_cmd_here_doc(t_node *list, t_arg *list_arg, t_data *data, t_node *base_node)
{
    (void)data;
    char *tmp_file_name;
    t_arg *current = list_arg;

    while (current) {
        // printf("\n\nJe suis le type|%s|\n", current->str_command);
        if (current->type == HEREDOC && current->next->type == DELIM) {
            current = current->next;
            tmp_file_name = ft_here_doc(data, list, current->str_command, base_node); // it's ok
            if (tmp_file_name == NULL)
            {
                free(tmp_file_name);
                data->exit_code = 130;
                return 1;
            }
            
            if (list->cmd->cmd != 0) // Ce qui permet de ne pas creer d'infile car il n'y a pas de commande
            {
                printf("\nJe suis le neouds |%s| et le type |%d|\n",current->str_command, current->type);
                free(current->str_command);
                current->str_command = tmp_file_name;
                current ->type = HEREDOC_INFILE;
                printf("\nJe suis le neouds |%s| et le type |%d|\n",current->str_command, current->type);

            }
            if(strncmp(tmp_file_name, "No_tmp_name",(size_t) (ft_strlen(tmp_file_name)== 0)))
            {
                printf("\nJe suis%s\n", tmp_file_name);
                free(tmp_file_name);
            }
        }
        current = current->next;
    }
    return (0);
}

void ft_verif_cmd(t_cmd **list, t_arg *list_arg)
{
    t_arg *arg = list_arg;
    int count;

    count = 0;

    while (arg)
    {
        if (arg->type == CMD)
        {
            // printf("Je suis la cmd |%s|", arg->str_command);
            count++;
        }
        arg = arg->next;
    }

    (*list)->cmd = count;
}
int is_builtin(const char *command) {
    if (strncmp(command, "echo", 4) == 0) {
        return 1;
    }
    if (strncmp(command, "env", 3) == 0) {
        return 1;
    }
    if (strncmp(command, "unset", 4) == 0) {
        return 1;
    }
    if (strncmp(command, "export", 6) == 0) {
        return 1;
    }
    if (strncmp(command, "cd", 2) == 0) {
        return 1;
    }
    if (strncmp(command, "pwd", 3) == 0) {
        return 1;
    }
    if (strncmp(command, "exit", 4) == 0) {
        return 1;
    }
    // Ajoutez d'autres commandes built-in ici
    return 0;
}

void ft_check_bulting(t_cmd **cmd, t_arg *arg)
{
    t_arg *tmp = arg;
    (void)cmd;
    //Creation d'une boucle permettant de verifier si la cammande est un bulting
    while(tmp)
    {
        if (tmp->type == CMD)
        {
             if (is_builtin(tmp->str_command)) 
             {
                (*cmd)->is_builtin = 1;
                // printf("La commande est un built-in.\n");
            }
        } 
        tmp = tmp->next;
    }
}
int    ft_check_infile_cmd(t_node *list, t_cmd **cmd, t_arg *arg)
{
    //1 er chose il faut boucler sur arg
    t_arg *tmp;
    t_iofile    *files;
    t_iofile    *new;
    int res;

    (void)cmd;
    tmp = arg;
    res = 0;
    files = NULL;
    while(tmp && res == 0)
    {
        if (tmp->type == INFILE || tmp->type == HEREDOC_INFILE)
        {
            new = malloc(sizeof(t_iofile));
            new->type = tmp->type;
            new->file = ft_strdup(tmp->str_command);
            new->next = NULL;
            if (files == NULL)
                list->cmd->input_str = new;
            else
                files->next = new;
            files = new;
        }
        tmp = tmp->next;
    }
    return(res);
}

void    ft_check_outfile(t_node *list, t_cmd **cmd, t_arg *arg)
{
    t_arg *tmp;
    t_iofile    *files;
    t_iofile    *new;

    (void)cmd;
    tmp = arg;
    files = NULL;
    while(tmp)
    {
        if(tmp->type == OUTFILE || tmp->type == APPEND)
        {
            new = malloc(sizeof(t_iofile));
            new->type = tmp->type;
            new->file = ft_strdup(tmp->str_command);
            new->next = NULL;

            if (files == NULL)
                list->cmd->output_str = new;
            else
                files->next = new;
            files = new;
        }


        // if(tmp->type == OUTFILE)
        // {
        //     ft_init_outfile(&list, tmp->str_command, 0);
        //     printf("\n |fd|%d|\n",(*cmd)->output);
        // }
        // if(tmp->type == APPEND)
        // {   
        //     ft_init_outfile(&list, tmp->str_command, 1);
        //     printf("\n |fd|%d|\n",(*cmd)->output);
        // }
        tmp= tmp->next;
    }

}
int lexer_cmd(t_node *list, t_data *data) // Cette fonction permet d'implementer list->cmd
{
    (void)data;
    t_node  *base_node;

    base_node = list;
    // verification acces list->arg//Start with list->arglist->cmd =
    while (list)
    {
        //printf("ICI");
        ft_init_cmd(&list->cmd);                     // it's ok
        ft_insert_double_tab(&list->cmd, list->arg); // it's ok
        ft_verif_cmd(&list->cmd, list->arg);         //it's ok//Pour le here_doc
        ft_check_outfile(list, &list->cmd, list->arg);//Il me semble qu'il manque un truc
        
        if (ft_insert_cmd_here_doc(list, list->arg, data, base_node) == 1)//it's ok plus ou moins
            return (1);
        ft_check_bulting(&list->cmd, list->arg);//it's ok
        if(ft_check_infile_cmd(list, &list->cmd, list->arg)==-1)
        {
            data->exit_code = 1;//it's ok
            return (1);
        }

        data->count = data->count + 1;//Permet de modifier le nom du infile pour le here_doc
        list = list->next; // todo check with heredoc
    }
    return (0);
    // IL faut maintenat voir si il y a here_doc et le placer en premeir
}

void lexer(t_node *list)
{
    while (list)
    {
       // printf("LIst = |%s|", list->arg->str_command);
        set_spec(list->arg);
        set_file(list->arg);
        set_cmd(list->arg);
        set_arg(list->arg);
        //print_arg(list->arg);
        list = list->next;
        // printf("\nXXX %p\n", list);
    }
}

static void set_spec(t_arg *elem) // sets redirection and pipes
{
    while (elem)
    {
        // printf("\nJe suis elequot|%d|\n", elem->quot);
        if (ft_strcmp(elem->str_command, "<<") == 0 && elem->quot == 2 )//C'est ici qu'il faut mettre une conditions
        {
            
            elem->type = HEREDOC;
            
        }    
        else if (ft_strcmp(elem->str_command, "<") == 0 && elem->quot == 2 )//C'est icic qu'il faut mettre une conditions
            elem->type = INPUT;
        else if (ft_strcmp(elem->str_command, ">>") == 0 && elem->quot == 2 )//C'est icic qu'il faut mettre une conditions
            elem->type = APPEND;
        else if (ft_strcmp(elem->str_command, ">") == 0 && elem->quot == 2 )//C'est icic qu'il faut mettre une conditions
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
