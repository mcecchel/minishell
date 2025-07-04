/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:59:11 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/04 17:44:06 by mbrighi          ###   ########.fr       */
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
	new_cmd->argv[0] = NULL; // IMPORTANTE: Inizializza
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
		return;
	}
	current = *cmd_list;
	while (current->next)
		current = current->next;
	current->next = new_cmd;
}

void	add_argument_to_cmd(t_cmd *cmd, char *arg)
{
	if (!cmd || !arg || !cmd->argv)
		return  ;
	if (cmd->argc >= 99) // Limite di sicurezza
	{
		ft_printf("Error: Too many arguments\n");
		return ;
	}
	cmd->argv[cmd->argc] = ft_strdup(arg);
	if (!cmd->argv[cmd->argc])
	{
		ft_printf("Error: Memory allocation failed\n");
		return;
	}
	cmd->argc++;
	cmd->argv[cmd->argc] = NULL; // SEMPRE termina l'array
}

int	is_redirection_token(t_token_type type)
{
	return (type == RED_IN || type == RED_OUT ||
			type == APPEND || type == HEREDOC);
}

int	handle_redirection(t_cmd *cmd, t_token *token)
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
		return (setup_heredoc(cmd, token->next->value));
	else
		return (0);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->argv)
		{
			int i = 0;
			while (tmp->argv[i])
			{
				free(tmp->argv[i]);
				i++;
			}
			free(tmp->argv);
		}
		if (tmp->infile != -1)
			close(tmp->infile);
		if (tmp->outfile != -1)
			close(tmp->outfile);
		free(tmp);
	}
}

t_cmd *parse_tokens(t_token *token_list)
{
	t_cmd	*cmd_list = NULL;
	t_cmd	*current_cmd = NULL;
	t_token	*token = token_list;

	while (token)
	{
		if (token->type == CMD)
		{
			// Crea nuovo comando
			current_cmd = init_new_cmd();
			if (!current_cmd)
			{
				free_cmd_list(cmd_list);
				return (NULL);
			}
			// Imposta comando e primo argomento
			current_cmd->cmd_path = ft_strdup(token->value);
			if (!current_cmd->cmd_path)
			{
				free_cmd_list(current_cmd);
				free_cmd_list(cmd_list);
				return (NULL);
			}
			current_cmd->argv[0] = ft_strdup(token->value);
			if (!current_cmd->argv[0])
			{
				free_cmd_list(current_cmd);
				free_cmd_list(cmd_list);
				return (NULL);
			}
			current_cmd->argc = 1;
			current_cmd->argv[1] = NULL;
			add_cmd_to_list(&cmd_list, current_cmd);
		}
		else if (token->type == ARG || token->type == FLAG)
		{
			if (!current_cmd)
			{
				ft_printf("Error: Argument without command\n");
				free_cmd_list(cmd_list);
				return (NULL);
			}
			add_argument_to_cmd(current_cmd, token->value);
		}
		else if (token->type == PIPE)
		{
			// Verifica che ci sia un comando dopo il pipe
			if (!token->next)
			{
				ft_printf("Error: Pipe without following command\n");
				free_cmd_list(cmd_list);
				return (NULL);
			}
			current_cmd = NULL; // Reset per il prossimo comando
		}
		else if (is_redirection_token(token->type))
		{
			if (!current_cmd)
			{
				ft_printf("Error: Redirection without command\n");
				free_cmd_list(cmd_list);
				return (NULL);
			}
			if (!handle_redirection(current_cmd, token))
			{
				free_cmd_list(cmd_list);
				return (NULL);
			}
			// Salta il token del filename
			if (token->next)
				token = token->next;
		}

		token = token->next;
	}
	// Verifica che abbiamo almeno un comando
	if (!cmd_list)
	{
		ft_printf("Error: No valid commands found\n");
		return (NULL);
	}
	return (cmd_list);
}
