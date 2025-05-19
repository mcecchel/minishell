/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:30:08 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/20 00:54:28 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <readline/history.h>
#include <signal.h>

void sigint_handler(int sig)
{
    (void)sig;
    // Vai a capo e mostra di nuovo il prompt
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);          // Pulisce la riga corrente
    rl_on_new_line();                // Si prepara a una nuova riga
    rl_redisplay();                  // Mostra il prompt di nuovo
}

int main(int argc, char **argv, char **envp)
{
	char *read_line;
	t_shell root = {0};


	root.env = copy_env(envp, root);
	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		read_line = readline("Prompt > ");

		if (read_line == NULL)
        {
            printf("\nexit\n");
            break;
        }
		printf("%s\n", read_line);
		free(read_line);
	}
	return (0);
}
