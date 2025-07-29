/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:30:08 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/28 19:00:31 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <readline/history.h>
#include <signal.h>

// Variabile globale
int	g_current_child_pid = -1;

void	reading(t_shell *shell)
{
	while (1)
	{
		if (!read_and_validate_line(shell))
			continue ;
		if (!handle_tokenization(shell))
			continue ;
		if (!handle_parsing(shell))
			continue ;
		handle_builtin_or_exec(shell);
		cleanup_shell(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_env	*env;

	shell = (t_shell){0};
	env = (t_env *){0};
	env = copy_env(envp);
	copy_system_envp_to_shell(envp, &shell);
	shell.env = env;
	(void)argc;
	(void)argv;
	shell.original_stdin = dup(STDIN_FILENO);
	shell.original_stdout = dup(STDOUT_FILENO);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	init_shell(&shell);
	reading(&shell);
	cleanup_shell(&shell);
	clean_exit(&shell);
	return (0);
}
