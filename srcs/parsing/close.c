/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:59:33 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 21:03:14 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_cmd_fds(t_cmd *cmd)
{
	if (cmd->infile != -1)
	{
		close(cmd->infile);
		cmd->infile = -1;
	}
	if (cmd->outfile != -1)
	{
		close(cmd->outfile);
		cmd->outfile = -1;
	}
}

void	close_all_cmd_fds(t_cmd *head)
{
	t_cmd	*current;

	current = head;
	while (current)
	{
		close_cmd_fds(current);
		current = current->next;
	}
}

void	close_outfile(t_cmd *cmd)
{
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = -1;
}
