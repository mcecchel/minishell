/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:41:19 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/29 17:19:10 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_arg_flag_token(t_cmd **current, t_cmd **cmd_list, t_token *tok)
{
	if (!*current)
	{
		fd_printf(2, "Error: Argument without command\n");
		free_cmd_list(*cmd_list);
		return (0);
	}
	add_argument_to_cmd(*current, tok->value);
	return (1);
}

int	handle_pipe_token(t_token *token, t_cmd **current, t_cmd **cmd_list,
		t_shell *shell)
{
	if (!*current || !*cmd_list)
	{
		fd_printf(2, "bash: syntax error near unexpected token `|'\n");
		shell->exit_value = 2;
		free_cmd_list(*cmd_list);
		return (0);
	}
	if (!token->next)
	{
		fd_printf(2, "Pipe syntax error\n");
		shell->exit_value = 2;
		free_cmd_list(*cmd_list);
		return (0);
	}
	if (token->next->type == PIPE)
	{
		fd_printf(2, "bash: syntax error near unexpected token `|'\n");
		shell->exit_value = 2;
		free_cmd_list(*cmd_list);
		return (0);
	}
	*current = NULL;
	return (1);
}

int	handle_cmd_token(t_cmd **cmd_list, t_cmd **cur, t_token **tok, t_shell *sh)
{
	t_cmd	*cmd;

	if (ft_strchr((*tok)->value, '=')
		&& check_export(sh, (*tok)->value, 0) == 0)
	{
		add_env(sh, (*tok)->value, VAR);
		return (2);
	}
	if (*cur && (*cur)->dummy_on)
	{
		handle_dummy_in_token(cur, tok);
		return (1);
	}
	cmd = create_base_cmd(*tok);
	if (!cmd || !cmd->cmd_path || !cmd->argv[0])
	{
		free_cmd_list(cmd);
		free_cmd_list(*cmd_list);
		return (0);
	}
	add_cmd_to_list(cmd_list, cmd);
	*cur = cmd;
	return (1);
}

void	handle_dummy_in_token(t_cmd **cur, t_token **tok)
{
	free((*cur)->cmd_path);
	free((*cur)->argv[0]);
	(*cur)->cmd_path = ft_strdup((*tok)->value);
	(*cur)->argv[0] = ft_strdup((*tok)->value);
	(*cur)->dummy_on = 0;
}

t_cmd	*create_base_cmd(t_token *token)
{
	t_cmd	*cmd;

	cmd = init_new_cmd();
	if (!cmd)
		return (NULL);
	cmd->cmd_path = ft_strdup(token->value);
	if (!cmd->cmd_path)
		return (cmd);
	cmd->argv[0] = ft_strdup(token->value);
	if (!cmd->argv[0])
		return (cmd);
	cmd->argc = 1;
	cmd->argv[1] = NULL;
	return (cmd);
}
