/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:28:53 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/02 20:39:28 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	// Crea una pipe per salvare l'input dell'heredoc
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		return (-1);
	}
	// Legge da stdin fino al delimitatore
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			close(pipe_fd[1]);
			return (pipe_fd[0]);
		}
		// Se la linea è uguale al delimitatore, termina
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		// Scrivi nella pipe e aggiungi un newline
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
} */

// sashi dice di lascire queste due da parte, dividere i comandi passati secondo le pipeline, eseguire heredoc
int setup_input_redir(t_cmd *cmd, char *filename)
{
	int fd;

	if (!cmd || !filename)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return (0);
	}
	// Chiudi il file descriptor precedente se esiste
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = fd;
	return (1);
}

int setup_output_redir(t_cmd *cmd, char *filename, int append)
{
	int fd;
	int flags;

	if (!cmd || !filename)
		return (0);
	// Scegli i flag in base al tipo di redirezione
	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (0);
	}
	// Chiudi il file descriptor precedente se esiste
	if (cmd->outfile != -1)
		close(cmd->outfile);
	cmd->outfile = fd;
	return (1);
}

/* int setup_heredoc(t_cmd *cmd, char *delimiter)
{
	int fd;

	if (!cmd || !delimiter)
		return (0);
	fd = handle_heredoc(delimiter);
	if (fd < 0)
		return (0);
	// Chiudi il file descriptor precedente se esiste
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = fd;
	return (1);
}
 */
