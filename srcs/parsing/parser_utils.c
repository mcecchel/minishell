/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:05:20 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/29 14:43:22 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_token(t_cmd **current, t_cmd **cmd_list, t_token **tok,
				t_shell *shell)
{
	if (!*current)
	{
		*current = init_new_cmd();
		if (!*current)
		{
			free_cmd_list(*cmd_list);
			return (0);
		}
		(*current)->cmd_path = ft_strdup("");
		(*current)->argv[0] = ft_strdup("");
		(*current)->argc = 1;
		(*current)->argv[1] = NULL;
		(*current)->dummy_on = 1;
		add_cmd_to_list(cmd_list, *current);
	}
	if (!handle_redirection(*current, *tok, shell))
	{
		free_cmd_list(*cmd_list);
		return (0);
	}
	return (1);
}

int	process_token(t_token *tok, t_cmd **cmd_list, t_cmd **current,
				t_shell *shell)
{
	int	ok;

	if (tok->type == ARG || tok->type == FLAG)
		ok = handle_arg_flag_token(current, cmd_list, tok);
	else if (tok->type == PIPE)
		ok = handle_pipe_token(tok, current, cmd_list, shell);
	else if (is_redirection_token(tok->type))
		ok = handle_redir_token(current, cmd_list, &tok, shell);
	else
		ok = 1;
	return (ok);
}

int	handle_cmd_advance(t_token **tok, t_cmd **cmd_list, t_cmd **current,
				t_shell *shell)
{
	int	ok;

	ok = handle_cmd_token(cmd_list, current, tok, shell);
	if (ok == 2)
	{
		*tok = (*tok)->next;
		return (2);
	}
	if (!ok)
		return (0);
	*tok = (*tok)->next;
	return (1);
}

int	handle_redirection_advance(t_token **tok, t_cmd **cmd_list, t_cmd **current,
				t_shell *shell)
{
	int	ok;

	ok = process_token(*tok, cmd_list, current, shell);
	if (!ok)
		return (0);
	*tok = (*tok)->next;
	if (*tok)
		*tok = (*tok)->next;
	return (1);
}
