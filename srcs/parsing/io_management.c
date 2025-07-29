/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_management.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:22:44 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 19:45:48 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stdio(t_shell *shell)
{
	if (shell->cmd->infile != -1)
	{
		dup2(shell->original_stdin, STDIN_FILENO);
		close(shell->cmd->infile);
	}
	if (shell->cmd->outfile != -1)
	{
		dup2(shell->original_stdout, STDOUT_FILENO);
		close(shell->cmd->outfile);
	}
}

void	redirect_stdio(t_cmd *cmd)
{
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			perror("dup2 (infile)");
	}
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			perror("dup2 (outfile)");
	}
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_current_child_pid = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	debug_cmds(t_cmd *cmd_list)
{
	int		cmd_index;
	t_cmd	*current;
	int		i;

	cmd_index = 0;
	current = cmd_list;
	if (!DEBUG)
		return ;
	while (current)
	{
		printf_debug("Command %d:\n", cmd_index++);
		printf_debug("  Path: %s\n", current->cmd_path);
		printf_debug("  Arguments: ");
		i = 0;
		while (current->argv && current->argv[i])
		{
			printf_debug("\"%s\" ", current->argv[i]);
			i++;
		}
		printf_debug("\n");
		printf_debug("  Infile: %d\n", current->infile);
		printf_debug("  Outfile: %d\n", current->outfile);
		current = current->next;
	}
}
