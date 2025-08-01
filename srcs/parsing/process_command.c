/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:45:04 by mcecchel          #+#    #+#             */
/*   Updated: 2025/08/01 19:59:10 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipe_for_command(t_cmd *current, int fd_pipe[2])
{
	if (current->next)
	{
		if (pipe(fd_pipe) == -1)
			return (-1);
		printf("pipe[%d][%d]\n", fd_pipe[0], fd_pipe[1]);
	}
	return (0);
}

int	fork_command_process(t_cmd *current, t_shell *shell, int fd_pipe[2])
{
	current->pid = fork();
	if (current->pid == -1)
	{
		error_fork(shell, fd_pipe, 1);
		return (-1);
	}
	return (0);
}

void	handle_process_roles(t_shell *shell, t_cmd *current,
						int *prev_pipe, int fd_pipe[2])
{
	if (current->pid == 0)
	{
		setup_child_process(current, *prev_pipe, fd_pipe, shell);
		execute_cmd(shell, current);
	}
	else
	{
		setup_parent_process(prev_pipe, fd_pipe, current);
	}
}

int	process_command_loop(t_shell *shell, t_cmd *current, int *prev_pipe)
{
	int	fd_pipe[2];

	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	while (current)
	{
		if (create_pipe_for_command(current, fd_pipe) == -1)
			return (error_fork(shell, fd_pipe, 0), -1);
		if (fork_command_process(current, shell, fd_pipe) == -1)
			return (-1);
		handle_process_roles(shell, current, prev_pipe, fd_pipe);
		current = current->next;
	}
	return (0);
}
