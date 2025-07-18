/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:38 by marianna          #+#    #+#             */
/*   Updated: 2025/07/18 16:29:07 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_error_handler(t_shell *shell, t_cmd *cmd, char *path, int err, int exit_code)
{
	if (err == 0)
		perror("dup2 error");
	if (err == 1)
		perror("Execve failed");
	if (err == 2)
		perror("Error dup2 prev_pipe");
	if (err == 3)
		perror("dup2 pipe_out");
	if (err == 4)
	{
	}
	if (cmd)
		close_cmd_fds(cmd);
	else
		close_cmd_fds(shell->cmd);
	cleanup_shell(shell);
	free_env_list(shell->env);
	free_matrix(shell->envp);
	if (path)
		free(path);
	exit (exit_code);
}


int	is_directory(char *path)
{
	int	is_a_folder;
	
	is_a_folder = open(path, __O_DIRECTORY);
	if (is_a_folder != -1)
	{
		close (is_a_folder);
		return (1);
	}
	close (is_a_folder);
	return (0);
}
void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			fork_error_handler(shell, cmd, NULL, 0, 1);
	}
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			fork_error_handler(shell, cmd, NULL, 0, 1);
	}
	if (cmd->cmd_path && ft_strlen(cmd->cmd_path) == 0)
		fork_error_handler(shell, cmd, NULL, 4, 0);
	if (parser_builtin(shell, cmd))
		fork_error_handler(shell, cmd, NULL, 4, shell->exit_value);
	path = get_cmd_path(shell, cmd, cmd->argv[0]);
	if (!path)
		fork_error_handler(shell, cmd, path, 1, 127);
	execve(path, cmd->argv, shell->envp);
	if (access(path, F_OK) != 0)
		fork_error_handler(shell, cmd, path, 1, 127);
	else if (access(path, X_OK) != 0)
		fork_error_handler(shell, cmd, path, 1, 126);
	else if (is_directory(path))
		fork_error_handler(shell, cmd, path, 1, 126);
	else
		fork_error_handler(shell, cmd, path, 1, 1);
}

void	print_envp_char(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
	{
		printf("envp is NULL\n");
		return ;
	}
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	execute_command_list(t_shell *shell)
{
	t_cmd	*current;
	int		fd_pipe[2];
	int		prev_pipe;

	current = shell->cmd;
	prev_pipe = -1;
	while (current)
	{
		if (current->next)
		{
			if (pipe(fd_pipe) == -1)
			{
				perror("Pipe error");
				return ;
			}
		}
		current->pid = fork();
		if (current->pid == -1)
		{
			perror("Fork error");
			return ;
		}
		if (current->pid == 0)
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
			execute_cmd(shell, current);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			if (prev_pipe != -1)
				close(prev_pipe);
			if (current->next)
			{
				close(fd_pipe[1]);
				prev_pipe = fd_pipe[0];
			}
			current = current->next;
		}
	}
	current = shell->cmd;
	while (current)
	{
		if (current->pid > 0)
		{
			int	status;
			if (waitpid(current->pid, &status, 0) != -1)
			{
				if (WIFEXITED(status))
					shell->exit_value = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
				{
					int sig = WTERMSIG(status);
					if (sig == SIGINT)
						shell->exit_value = 130;
					else if (sig == SIGQUIT)
						shell->exit_value = 131;
				}
			}
		}
		current = current->next;
	}
	signal(SIGINT, sigint_handler);
	if (prev_pipe != -1)
		close(prev_pipe);
}
