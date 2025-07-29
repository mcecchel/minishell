/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:57:57 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/29 15:32:53 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_command_loop(t_shell *shell, t_cmd *current, int *prev_pipe)
{
	int	fd_pipe[2];

	while (current)
	{
		if (handle_pipe_creation(current, fd_pipe) == -1)
			return (-1);
		if (handle_fork_creation(current) == -1)
			return (-1);
		if (current->pid == 0)
		{
			setup_child_process(current, *prev_pipe, fd_pipe);
			execute_cmd(shell, current);
		}
		else
		{
			setup_parent_process(*prev_pipe, fd_pipe, current);
			*prev_pipe = update_prev_pipe(current, fd_pipe, *prev_pipe);
			current = current->next;
		}
	}
	return (0);
}

int	handle_fork_creation(t_cmd *current)
{
	current->pid = fork();
	if (current->pid == -1)
	{
		perror("Fork error");
		return (-1);
	}
	return (0);
}

void	setup_child_process(t_cmd *current, int prev_pipe, int *fd_pipe)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_pipe != -1)
	{
		if (current->infile == -1)
			current->infile = prev_pipe;
		else
			close(prev_pipe);
	}
	if (current->next)
	{
		close(fd_pipe[0]);
		if (current->outfile == -1)
			current->outfile = fd_pipe[1];
		else
			close(fd_pipe[1]);
	}
}

void	setup_parent_process(int prev_pipe, int *fd_pipe, t_cmd *current)
{
	signal(SIGINT, SIG_IGN);
	if (prev_pipe != -1)
		close(prev_pipe);
	if (current->next)
		close(fd_pipe[1]);
}

int	handle_standard_advance(t_token **tok, t_cmd **cmd_list,
				t_cmd **current, t_shell *shell)
{
	int	ok;

	ok = process_token(*tok, cmd_list, current, shell);
	if (!ok)
		return (0);
	*tok = (*tok)->next;
	return (1);
}
