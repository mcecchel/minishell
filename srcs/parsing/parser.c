/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:00:50 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/29 14:52:05 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		fd_printf(2, "Error: Too many arguments\n");
		return ;
	}
	new_arg = ft_strdup(arg);
	if (!new_arg)
	{
		fd_printf(2, "Error: Memory allocation failed\n");
		return ;
	}
	cmd->argv[cmd->argc] = new_arg;
	cmd->argc++;
	cmd->argv[cmd->argc] = NULL;
}

char	*get_cmd_path(t_shell *shell, t_cmd *cmd, char *command)
{
	char	**paths;
	char	*full_path;

	if (!is_valid_command(cmd, command))
		return (NULL);
	if (access(command, F_OK | X_OK) == 0 && ft_strchr(command, '/'))
		return (ft_strdup(command));
	paths = get_paths(shell);
	if (!paths)
		return (NULL);
	full_path = search_command(paths, command);
	if (!full_path)
		return (free_matrix(paths), NULL);
	return (full_path);
}
