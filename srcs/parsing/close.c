/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:59:33 by mbrighi           #+#    #+#             */
/*   Updated: 2025/08/01 16:42:40 by mbrighi          ###   ########.fr       */
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

void	close_pipe(int *pipe_fd)
{
	if (pipe_fd[0] != -1)
	{
		close(pipe_fd[0]);
		pipe_fd[0] = -1;
	}
	if (pipe_fd[1] != -1)
	{
		close(pipe_fd[1]);
		pipe_fd[1] = -1;
	}
}

void	close_unused_fds(t_cmd *current)
{
	t_cmd	*tmp;

	tmp = current->next;
	while (tmp)
	{
		if (tmp->infile != -1 && tmp->infile != current->infile)
			close(tmp->infile);
		if (tmp->outfile != -1 && tmp->outfile != current->outfile)
			close(tmp->outfile);
		tmp = tmp->next;
	}
}
