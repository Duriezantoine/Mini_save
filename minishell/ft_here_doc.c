
#include "minishell.h"
static volatile sig_atomic_t	signal_recu = 0;


void	ft_here_doc(char *value, t_data *data, char *envp[])
{
	char				*write_here_do;
	int					ret;
	int					test;
	struct sigaction	action;
	struct termios		term_attr;

	ft_init_signaux(&action, &write_here_do);
	tcgetattr(STDIN_FILENO, &term_attr);
	ret = read(0, write_here_do, 1023);
	write_here_do[ret] = '\n';
	while (1)
	{
		test = strcmp(write_here_do, value);
		if (ret == 0)
		{
			break ;
		}
		if (test - 10 == 0)
			break ;
		if (signal_recu == -2)
		{
			shell_loop(&data, envp);
			break ;
		}
		ret = read(0, write_here_do, 1023);
		write_here_do[ret] = '\0';
	}
}

