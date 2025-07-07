/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:38 by marianna          #+#    #+#             */
/*   Updated: 2025/07/07 17:08:23 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_error_handler(t_shell *shell, char *path, int err, int exit_code)
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
		;
	close_cmd_fds(shell->cmd);
	cleanup_shell(shell);
	free_env_list(shell->env);
	free_split(shell->envp);
	if (path)
		free(path);
	exit (exit_code);
}

void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	shell->cmd = cmd;
	if (cmd->infile != -1) // Gestione redirezioni INPUT
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
			fork_error_handler(shell, NULL, 0, 1);
	}
	if (cmd->outfile != -1) // Gestione redirezioni OUTPUT
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
			fork_error_handler(shell, NULL, 0, 1);
	}
	if (parser_builtin(shell))
		fork_error_handler(shell, NULL, 4, shell->exit_value);
	path = get_cmd_path(shell, cmd, cmd->argv[0]);
	if (!path)
		exit(127); // Command not found
	execve(path, cmd->argv, shell->envp);
	if (access(path, F_OK) != 0)
		fork_error_handler(shell, path, 1, 127);
	else if (access(path, X_OK) != 0)
		fork_error_handler(shell, path, 1, 126);
	else
		fork_error_handler(shell, path, 1, 1);
}

void	print_envp_char(char **envp)
{
	int i = 0;
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
		// Se non è l'ultimo comando, crea una pipe
		if (current->next)
		{
			if (pipe(fd_pipe) == -1)
			{
				perror("Pipe error");
				return;
			}
		}
		current->pid = fork();
		if (current->pid == -1)
		{
			perror("Fork error");
			return;
		}
		if (current->pid == 0) // Processo figlio
		{
			// Collega l'input alla pipe precedente se esiste
			if (prev_pipe != -1)
			{
				if (dup2(prev_pipe, STDIN_FILENO) == -1)
					fork_error_handler(shell, NULL, 2, 1);
				close(prev_pipe);
			}
			// Se non è l'ultimo comando, collega l'output alla nuova pipe
			if (current->next)
			{
				close(fd_pipe[0]);
				
				// Solo se non c'è già una redirezione di output
				if (current->outfile == -1)
				{
					if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
						fork_error_handler(shell, NULL, 3, 1);
				}
				close(fd_pipe[1]); // Chiudi write end
			}
			execute_cmd(shell, current);
		}
		else // Processo padre
		{
			// Chiudi la pipe precedente se esiste
			if (prev_pipe != -1)
				close(prev_pipe);
			// Se non è l'ultimo comando, aggiorna prev_pipe
			if (current->next)
			{
				close(fd_pipe[1]); // Chiudi write end
				prev_pipe = fd_pipe[0]; // Salva read end
			}
			current = current->next;
		}
	}
	// Aspetta che tutti i processi figli terminino
	current = shell->cmd;
	while (current)
	{
		if (current->pid > 0)
		{
			int status;
			if (waitpid(current->pid, &status, 0) != -1)
			{
				// Aggiorna l'exit value con l'ultimo comando
				if (WIFEXITED(status))
					shell->exit_value = WEXITSTATUS(status);
				else
					shell->exit_value = 1;
			}
		}
		current = current->next;
	}
	// Chiudi l'ultima pipe se esiste
	if (prev_pipe != -1)
		close(prev_pipe);
}
