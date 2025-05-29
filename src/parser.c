/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:59:11 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/29 18:16:14 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *init_new_cmd(void)
{
    t_cmd *new_cmd;

    new_cmd = ft_calloc(1, sizeof(t_cmd));
    if (!new_cmd)
        return (NULL);

    new_cmd->cmd_path = NULL;  // Inizializza a NULL
    new_cmd->argv = ft_calloc(sizeof(char *), 100);
    if (!new_cmd->argv)
    {
        free(new_cmd);
        return (NULL);
    }
    new_cmd->argc = 0;
    new_cmd->infile = -1;
    new_cmd->outfile = -1;
    new_cmd->pid = -1;
    new_cmd->next = NULL;
    return (new_cmd);
}

void	add_cmd(t_cmd *cmd, t_cmd *new_cmd)
{
	t_cmd	*current_cmd;

	if (!cmd || !new_cmd)
		return ;
	if (!cmd->next)
	{
		cmd->next = new_cmd;
	}
	else
	{
		current_cmd = cmd;
		while (current_cmd->next)
			current_cmd = current_cmd->next;
		current_cmd->next = new_cmd;
	}
}

void add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd)
{
    t_cmd *current;

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

void add_argument_to_cmd(t_cmd *cmd, char *arg)
{
    if (!cmd || !arg)
        return;

    if (cmd->argc >= 99) // Limite di sicurezza
        return;
    cmd->argv[cmd->argc] = ft_strdup(arg);
    cmd->argc++;
    cmd->argv[cmd->argc] = NULL;
}

int is_redirection_token(t_token_type type)
{
    return (type == RED_IN || type == RED_OUT ||
            type == APPEND || type == HEREDOC);
}

int handle_redirection(t_cmd *cmd, t_token *token)
{
    if (!token->next)
    {
        ft_printf("Error: Missing file for redirection\n");
        return (0);
    }
    if (token->type == RED_IN)
        return (setup_input_redirection(cmd, token->next->value));
    else if (token->type == RED_OUT)
        return (setup_output_redirection(cmd, token->next->value, 0));
    else if (token->type == APPEND)
        return (setup_output_redirection(cmd, token->next->value, 1));
    else if (token->type == HEREDOC)
        return (setup_heredoc(cmd, token->next->value));
    else
        return (0);
}

t_cmd *parse_tokens(t_token *token_list)
{
    t_cmd *cmd_list = NULL;
    t_cmd *current_cmd = NULL;
    t_token *token = token_list;
    int first_cmd = 1;

    while (token)
    {
        if (token->type == CMD || (token->type == ARG && !current_cmd))
        {
            // Se è il primo comando o dopo un pipe
            if (first_cmd || (token->type == ARG && !current_cmd))
            {
                current_cmd = init_new_cmd();
                if (!current_cmd)
                    return (free_cmd_list(cmd_list), NULL);

                current_cmd->cmd_path = ft_strdup(token->value);
                current_cmd->argv[0] = ft_strdup(token->value);
                current_cmd->argc = 1;

                if (!cmd_list)
                    cmd_list = current_cmd;
                else
                    add_cmd_to_list(&cmd_list, current_cmd);

                first_cmd = 0;
            }
        }
        else if (token->type == ARG || token->type == FLAG ||
                 token->type == QUOTE || token->type == DQUOTE)
        {
            if (!current_cmd)
            {
                ft_printf("Error: Argument without command\n");
                return (free_cmd_list(cmd_list), NULL);
            }
            add_argument_to_cmd(current_cmd, token->value);
        }
        else if (token->type == PIPE)
        {
            if (!token->next)
            {
                ft_printf("Error: Pipe at end of command\n");
                return (free_cmd_list(cmd_list), NULL);
            }
            current_cmd = NULL; // Reset per il prossimo comando
        }
        else if (is_redirection_token(token->type))
        {
            if (!current_cmd)
            {
                ft_printf("Error: Redirection without command\n");
                return (free_cmd_list(cmd_list), NULL);
            }
            if (!handle_redirection(current_cmd, token))
            {
                return (free_cmd_list(cmd_list), NULL);
            }
            token = token->next; // Salta il nome del file
        }

        token = token->next;
    }

    return (cmd_list);
}
