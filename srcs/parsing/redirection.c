/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:14:06 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/31 19:06:16 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_input_redir(t_cmd *cmd, char *filename)
{
	int	fd;

	if (!cmd || !filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return (0);
	}
	if (cmd->infile != -1 && cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	cmd->infile = fd;
	return (1);
}

int	setup_output_redir(t_cmd *cmd, char *filename, int append)
{
	int	fd;
	int	flags;

	if (!filename)
		return (0);
	if (cmd->outfile != -1 && cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror(filename);
		cmd->outfile = -1;
		return (0);
	}
	cmd->outfile = fd;
	return (1);
}

static void	print_and_error(t_shell *shell)
{
	fd_printf(2, "Error: Invalid redirection target\n");
	shell->exit_value = 2;
}

int	handle_redirection(t_cmd *cmd, t_token *token, t_shell *shell)
{
	if (!token->next)
		return (print_and_error(shell), 0);
	if (token->next->type != ARG && token->next->type != CMD)
		return (print_and_error(shell), 0);
	if (token->type == RED_IN)
		return (setup_input_redir(cmd, token->next->value));
	else if (token->type == RED_OUT)
		return (setup_output_redir(cmd, token->next->value, 0));
	else if (token->type == APPEND)
		return (setup_output_redir(cmd, token->next->value, 1));
	else if (token->type == HEREDOC)
		return (setup_heredoc(cmd, token->next->value, shell,
				token->next->is_quoted));
	return (0);
}

int	is_redirection_token(t_token_type type)
{
	return (type == RED_IN || type == RED_OUT
		|| type == APPEND || type == HEREDOC);
}
