/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:57:57 by mbrighi           #+#    #+#             */
/*   Updated: 2025/08/01 17:25:39 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	process_command_loop(t_shell *shell, t_cmd *current, int *prev_pipe)
// {
// 	int	fd_pipe[2];

// 	fd_pipe[0] = -1;
// 	fd_pipe[1] = -1;
// 	while (current)
// 	{
// 		if (handle_pipe_creation(current, fd_pipe) == -1)
// 			return (close_pipe(fd_pipe), -1);
// 		if (handle_fork_creation(current) == -1)
// 			return (close_pipe(fd_pipe), -1);
// 		if (current->pid == 0)
// 		{
// 			setup_child_process(current, *prev_pipe, fd_pipe, shell);
// 			execute_cmd(shell, current);
// 		}
// 		else
// 		{
// 			setup_parent_process(*prev_pipe, fd_pipe, current);
// 			*prev_pipe = update_prev_pipe(current, fd_pipe, *prev_pipe);
// 			current = current->next;
// 		}
// 	}
// 	return (0);
// }

void	close_all_fds_on_error(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		close_all_cmd_fds(current);
		current = current->next;
	}
}

int	process_command_loop(t_shell *shell, t_cmd *current, int *prev_pipe)
{
	int	fd_pipe[2];

	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	while (current)
	{
		if (current->next){

			if (pipe(fd_pipe) == -1)
				return (error_fork(shell, fd_pipe, 0), -1);
			printf("pipe[%d][%d]\n", fd_pipe[0], fd_pipe[1]);
		}
		current->pid = fork();
		if (current->pid == -1)
			return (error_fork(shell, fd_pipe, 1), -1);
		if (current->pid == 0)
		{
			setup_child_process(current, *prev_pipe, fd_pipe, shell);
			execute_cmd(shell, current);
		}
		else
		{
			setup_parent_process(prev_pipe, fd_pipe, current);
			// *prev_pipe = update_prev_pipe(current, fd_pipe, *prev_pipe);
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

void	setup_child_process(t_cmd *current, int prev_pipe, int *fd_pipe, t_shell *shell)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	close_pipe(fd_pipe);
	if (prev_pipe != -1)
		close(prev_pipe);
	close(shell->original_stdin);
	close(shell->original_stdout);
	close_unused_fds(current);
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
