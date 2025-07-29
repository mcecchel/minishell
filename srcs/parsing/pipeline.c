/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:56:56 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 20:23:21 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_children_safe(t_cmd *cmd_list, t_shell *shell)
{
	t_cmd	*current;
	int		status;
	int		sig;

	current = cmd_list;
	while (current)
	{
		if (current->pid > 0)
		{
			if (waitpid(current->pid, &status, 0) != -1)
			{
				if (WIFEXITED(status))
					shell->exit_value = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
				{
					sig = WTERMSIG(status);
					if (sig == SIGINT)
						shell->exit_value = 130;
					else if (sig == SIGQUIT)
						shell->exit_value = 131;
				}
			}
		}
		current = current->next;
	}
}

int	update_prev_pipe(t_cmd *current, int *fd_pipe, int prev_pipe)
{
	if (current->next)
		return (fd_pipe[0]);
	return (prev_pipe);
}

int	handle_pipe_creation(t_cmd *current, int *fd_pipe)
{
	if (current->next)
	{
		if (pipe(fd_pipe) == -1)
		{
			perror("Pipe error");
			return (-1);
		}
	}
	return (0);
}
