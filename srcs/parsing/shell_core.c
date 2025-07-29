/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:20:14 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/29 17:13:05 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_and_validate_line(t_shell *shell)
{
	shell->line = readline("minishell> ");
	status_code_update(shell);
	if (!shell->line)
	{
		write(1, "exit\n", 5);
		clean_exit(shell);
		cleanup_shell(shell);
		exit((unsigned char)shell->exit_value);
	}
	if (*shell->line == '\0')
	{
		free(shell->line);
		shell->line = NULL;
		return (0);
	}
	add_history(shell->line);
	return (1);
}

int	handle_tokenization(t_shell *shell)
{
	if (!tokenize_input(&shell->token, &shell->line, shell))
	{
		cleanup_shell(shell);
		return (0);
	}
	printf_debug("Generated tokens:\n");
	debug_tokens(shell->token.head);
	return (1);
}

int	handle_parsing(t_shell *shell)
{
	shell->cmd = parse_tokens(shell->token.head, shell);
	if (!shell->cmd)
	{
		cleanup_shell(shell);
		return (0);
	}
	shell->cmd = optimize_command_list(shell->cmd);
	printf_debug("\nGenerated commands:\n");
	debug_cmds(shell->cmd);
	return (1);
}

void	handle_builtin_or_exec(t_shell *shell)
{
	if (shell->cmd && !shell->cmd->next
		&& (is_dummy_command(shell->cmd)
			|| is_builtin(shell->cmd->cmd_path)))
	{
		if (is_builtin(shell->cmd->cmd_path))
		{
			redirect_stdio(shell->cmd);
			parser_builtin(shell, shell->cmd);
			restore_stdio(shell);
		}
	}
	else
		execute_command_list(shell);
}
