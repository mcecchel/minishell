/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:50:36 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 21:06:17 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (cmd->infile != -1)
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			fork_error_handler(shell, cmd, 0, 1);
	if (cmd->outfile != -1)
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			fork_error_handler(shell, cmd, 0, 1);
	if (cmd->cmd_path && ft_strlen(cmd->cmd_path) == 0)
		fork_error_handler(shell, cmd, 4, 0);
	if (is_builtin(cmd->cmd_path))
	{
		if (parser_builtin(shell, cmd))
			fork_error_handler(shell, cmd, 4, shell->exit_value)
			;
	}
	path = get_cmd_path(shell, cmd, cmd->argv[0]);
	if (!path)
		fork_error_handler(shell, cmd, 1, 127);
	execve(path, cmd->argv, shell->envp);
	execve_failed(shell, cmd, path);
}

void	execute_command_list(t_shell *shell)
{
	t_cmd	*current;
	t_cmd	*cmd_list;
	int		prev_pipe;

	current = shell->cmd;
	cmd_list = shell->cmd;
	prev_pipe = -1;
	if (process_command_loop(shell, current, &prev_pipe) == -1)
		return ;
	wait_for_children_safe(cmd_list, shell);
	signal(SIGINT, sigint_handler);
	if (prev_pipe != -1)
		close(prev_pipe);
}

void	cleanup_shell(t_shell *shell)
{
	if (shell->cmd)
	{
		free_cmd_list(shell->cmd);
		shell->cmd = NULL;
	}
	if (shell->token.head)
	{
		free_tokens(shell->token.head);
		shell->token.head = NULL;
		shell->token.current = NULL;
	}
	free(shell->line);
	shell->line = NULL;
}
