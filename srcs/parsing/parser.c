/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:59:11 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/19 18:44:36 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Inizializzazione comando migliorata
t_cmd	*init_new_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->argv = ft_calloc(sizeof(char *), 100);
	if (!new_cmd->argv)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->cmd_path = NULL;
	new_cmd->argc = 0;
	new_cmd->argv[0] = NULL;
	new_cmd->infile = -1;
	new_cmd->outfile = -1;
	new_cmd->pid = -1;
	new_cmd->next = NULL;
	return (new_cmd);
}

void	add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		return ;
	}
	current = *cmd_list;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

void	add_argument_to_cmd(t_cmd *cmd, char *arg)
{
	char	*new_arg;

	if (!cmd || !arg || !cmd->argv)
		return ;
	if (cmd->argc >= 99)
	{
		ft_printf("Error: Too many arguments\n");
		return ;
	}
	new_arg = ft_strdup(arg);
	if (!new_arg)
	{
		ft_printf("Error: Memory allocation failed\n");
		return ;
	}
	cmd->argv[cmd->argc] = new_arg;
	cmd->argc++;
	cmd->argv[cmd->argc] = NULL;
}

int	is_redirection_token(t_token_type type)
{
	return (type == RED_IN || type == RED_OUT
		|| type == APPEND || type == HEREDOC);
}

int	handle_redirection(t_cmd *cmd, t_token *token, t_shell *shell)
{
	if (!token->next)
	{
		ft_printf("Error: Missing file for redirection\n");
		return (0);
	}
	if (token->next->type != ARG && token->next->type != CMD)
	{
		ft_printf("Error: Invalid redirection target\n");
		return (0);
	}
	if (token->type == RED_IN)
		return (setup_input_redir(cmd, token->next->value));
	else if (token->type == RED_OUT)
		return (setup_output_redir(cmd, token->next->value, 0));
	else if (token->type == APPEND)
		return (setup_output_redir(cmd, token->next->value, 1));
	else if (token->type == HEREDOC)
		return (setup_heredoc(cmd, token->next->value, shell,
				token->next->is_quoted));
	else
		return (0);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->heredoc_delimiter)
			free(tmp->heredoc_delimiter);
		if (tmp->argv)
		{
			i = 0;
			while (tmp->argv[i])
			{
				free(tmp->argv[i]);
				i++;
			}
			free(tmp->argv);
		}
		close_cmd_fds(tmp);
		free(tmp);
	}
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

int	handle_cmd_token(t_cmd **cmd_list, t_cmd **cur, t_token **tok, t_shell *sh)
{
	t_cmd	*cmd;

	if (ft_strchr((*tok)->value, '=')
		&& check_export(sh, (*tok)->value, 0) == 0)
	{
		add_env(sh, (*tok)->value, VAR);
		return (2);
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

int	handle_arg_flag_token(t_cmd **current, t_cmd **cmd_list, t_token *tok)
{
	if (!*current)
	{
		ft_printf("Error: Argument without command\n");
		free_cmd_list(*cmd_list);
		return (0);
	}
	add_argument_to_cmd(*current, tok->value);
	return (1);
}

int	handle_pipe_token(t_token *token, t_cmd **current, t_cmd **cmd_list)
{
	if (!token->next)
	{
		ft_printf("Pipe syntax error\n");
		free_cmd_list(*cmd_list);
		return (0);
	}
	*current = NULL;
	return (1);
}

static int	handle_redir_token(t_cmd **current,
				t_cmd **cmd_list, t_token **tok, t_shell *sh)
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
	if (!handle_redirection(*current, *tok, sh))
	{
		free_cmd_list(*cmd_list);
		return (0);
	}
	return (1);
}

static int	process_token(t_token *tok, t_cmd **cmd_list, 
				t_cmd **current, t_shell *shell)
{
	int	ok;

	if (tok->type == ARG || tok->type == FLAG)
		ok = handle_arg_flag_token(current, cmd_list, tok);
	else if (tok->type == PIPE)
		ok = handle_pipe_token(tok, current, cmd_list);
	else if (is_redirection_token(tok->type))
		ok = handle_redir_token(current, cmd_list, &tok, shell);
	else
		ok = 1;
	return (ok);
}

static int	handle_cmd_advance(t_token **tok, t_cmd **cmd_list,
				t_cmd **current, t_shell *shell)
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

static int	handle_redirection_advance(t_token **tok, t_cmd **cmd_list,
				t_cmd **current, t_shell *shell)
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

static int	handle_standard_advance(t_token **tok, t_cmd **cmd_list,
				t_cmd **current, t_shell *shell)
{
	int	ok;

	ok = process_token(*tok, cmd_list, current, shell);
	if (!ok)
		return (0);
	*tok = (*tok)->next;
	return (1);
}

static int	handle_token_in_loop(t_token **tok, t_cmd **cmd_list,
				t_cmd **current, t_shell *shell)
{
	if ((*tok)->type == CMD)
		return (handle_cmd_advance(tok, cmd_list, current, shell));
	else if (is_redirection_token((*tok)->type))
		return (handle_redirection_advance(tok, cmd_list, current, shell));
	else
		return (handle_standard_advance(tok, cmd_list, current, shell));
}

t_cmd	*parse_tokens(t_token *tokens, t_shell *shell)
{
	t_cmd		*cmd_list;
	t_cmd		*current;
	t_token		*tok;
	int			result;

	cmd_list = NULL;
	current = NULL;
	tok = tokens;
	while (tok)
	{
		result = handle_token_in_loop(&tok, &cmd_list, &current, shell);
		if (result == 0)
			return (NULL);
		if (result == 2)
			continue ;
	}
	if (!cmd_list)
		return (NULL);
	return (cmd_list);
}
