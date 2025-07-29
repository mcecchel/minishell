/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:16:41 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 21:05:53 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_matrix(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	debug_tokens(t_token *token)
{
	int	i;

	if (!DEBUG)
		return ;
	i = 0;
	while (token)
	{
		printf_debug("[%d] Token: \"%s\" | Type: %s", i, token->value,
			obtain_token_type(token));
		if (token->is_quoted)
			printf_debug(" (QUOTED)");
		printf_debug("\n");
		token = token->next;
		i++;
	}
}

int	is_valid_command(t_cmd *cmd, char *command)
{
	if (command == NULL || *command == '\0' || is_space(*command) == 1)
	{
		perror("Error: Invalid command");
		if (cmd->infile != -1)
			close(cmd->infile);
		if (cmd->outfile != -1)
			close(cmd->outfile);
		return (0);
	}
	return (1);
}
