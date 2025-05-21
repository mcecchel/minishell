/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:59:11 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/21 17:32:46 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_new_cmd(t_cmd *cmd)
{
	t_cmd	*new_cmd;

	if (!cmd)
	{
		ft_printf("Error: Input command is NULL\n");
		return (NULL);
	}
	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
	{
		ft_printf("Error: Memory allocation failed for new command\n");
		return (NULL);
	}
	new_cmd->cmd_path = ft_strdup(cmd->cmd_path);
	if (!new_cmd->cmd_path)
	{
		ft_printf("Error: Memory allocation failed for cmd_path\n");
		free(new_cmd);
		return (NULL);
	}
	new_cmd->argv = ft_calloc(sizeof(char *), 100);
	if (!new_cmd->argv)
	{
		ft_printf("Error: Memory allocation failed for argv\n");
		free(new_cmd->cmd_path);
		free(new_cmd);
		return (NULL);
	}
	new_cmd->argv[0] = NULL;
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
