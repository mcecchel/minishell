/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:50:51 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/01 19:58:03 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_child_pipes(t_cmd *current, int prev_pipe, int *fd_pipe,
		t_shell *shell)
{
	if (prev_pipe != -1 && current->infile == -1)
	{
		if (dup2(prev_pipe, STDIN_FILENO) == -1)
		{
			perror("dup2 prev_pipe");
			close(prev_pipe);
			close_pipe(fd_pipe);
			fork_error_handler(shell, current, 4, 1);
		}
	}
	if (current->next && fd_pipe[1] != -1 && current->outfile == -1)
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe_out");
			shell->exit_value = 1;
			close_pipe(fd_pipe);
			fork_error_handler(shell, current, 4, 1);
		}
	}
}

void	cleanup_child_fds(t_cmd *current, int prev_pipe, int *fd_pipe,
		t_shell *shell)
{
	close_pipe(fd_pipe);
	if (prev_pipe != -1)
		close(prev_pipe);
	close(shell->original_stdin);
	close(shell->original_stdout);
	close_unused_fds(current);
}

void	setup_child_process(t_cmd *current, int prev_pipe, int *fd_pipe,
		t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	setup_child_pipes(current, prev_pipe, fd_pipe, shell);
	cleanup_child_fds(current, prev_pipe, fd_pipe, shell);
}

void	setup_parent_process(int *prev_pipe, int *fd_pipe, t_cmd *current)
{
	(void)current;
	signal(SIGINT, SIG_IGN);
	if (*prev_pipe != -1)
		close(*prev_pipe);
	*prev_pipe = fd_pipe[0];
	if (fd_pipe[1] != -1)
		close(fd_pipe[1]);
}
