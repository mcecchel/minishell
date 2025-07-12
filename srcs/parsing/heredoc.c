/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:58:47 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/11 19:49:10 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Configurazione segnali per heredoc
void	handle_heredoc_signal(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);// Pulisce la riga corrente
	rl_on_new_line();// Si prepara a una nuova riga
	rl_redisplay();// Mostra il prompt di nuovo
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_heredoc_signal);
	signal(SIGQUIT, SIG_IGN); // Ignora SIGQUIT durante l'heredoc
}

void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL); // Ripristina comportamento predefinito di SIGINT
	signal(SIGQUIT, SIG_DFL); // Ripristina comportamento predefinito di SIGQUIT
}

char	*expand_heredoc(t_shell *shell, char *line, int expand)
{
	char	*expanded_line;
	char	*res;

	if (!line)
		return (NULL);
	if (expand)
		expanded_line = expand_variables(line, shell, 0);
	else
		expanded_line = ft_strdup(line);
	if (!expanded_line)
		return (NULL);
	res = ft_strjoin(expanded_line, "\n");
	free(expanded_line);
	if (!res)
	{
		perror("Error expanding heredoc");
		return (NULL);
	}
	return (res);
}

// Controllo se il delimitatore è quotato
int	is_delimiter_quoted(char *delimiter)
{
	if (!delimiter)
		return (0);
	if (delimiter[0] == '\'' || delimiter[0] == '\"')
		return (1);
	return (0);
}

// Rimuove le quote dal delimitatore (se presenti)
char	*remove_quotes_from_delimiter(char *delimiter)
{
	char	*new_delimiter;
	int		i;
	int		j;

	if (!delimiter)
		return (NULL);
	new_delimiter = ft_calloc(ft_strlen(delimiter) + 1, sizeof(char));
	if (!new_delimiter)
		return (NULL);
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] != '\'' && delimiter[i] != '\"')
			new_delimiter[j++] = delimiter[i];
		i++;
	}
	new_delimiter[j] = '\0';
	// Se e' una stringa vuota freeo e ritorno NULL
	if (j == 0)
	{
		free(new_delimiter);
		return (NULL);
	}
	return (new_delimiter);
}

// Crea un file temporaneo per l'heredoc
char	*create_tmp_heredoc_file(void)
{
	static int	heredoc_count;
	char		*filename;
	char		*count_str;

	count_str = ft_itoa(heredoc_count++);
	if (!count_str)
	{
		perror("Error: Failed to convert heredoc count to string");
		return (NULL);
	}
	filename = ft_strjoin("heredoc", count_str);
	free(count_str);
	if (!filename)
	{
		perror("Error: Failed to create heredoc filename");
		return (NULL);
	}
	return (filename);
}

// Gestione input heredoc
int	handle_heredoc_input(t_shell *shell, char *delimiter)
{
	char	*line;
	char	*clean_delimiter;
	char	*tmp_file;
	int		fd;
	char	*expanded_line;
	int		ret_fd;

	clean_delimiter = remove_quotes_from_delimiter(delimiter);
	if (!clean_delimiter)
	{
		perror("Error removing quotes from delimiter");
		return (-1);
	}
	tmp_file = create_tmp_heredoc_file();
	if (!tmp_file)
	{
		free(clean_delimiter);
		return (-1);
	}
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error: Failed to open heredoc file");
		free(clean_delimiter);
		free(tmp_file);
		return (-1);
	}
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(STDOUT_FILENO, "\n", 1);
			close(fd);
			unlink(tmp_file);// Rimuove il file temporaneo in caso di interruzione
			free(clean_delimiter);
			free(tmp_file);
			return (-1);// Interruzione dell'input heredoc
		}
		if (ft_strcmp(line, clean_delimiter) == 0)
		{
			free(line);
			break;// Esce dal ciclo se il delim e' stato inserito
		}
		expanded_line = expand_heredoc(shell, line, 1);
		if (expanded_line)
		{
			write(fd, expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
		free(line);
	}
	close(fd);
	ret_fd = open(tmp_file, O_RDONLY);
	unlink(tmp_file);
	free(clean_delimiter);
	free(tmp_file);
	return (ret_fd);
}

int setup_heredoc(t_cmd *cmd, char *delimiter, t_shell *shell)
{
	int fd;

	if (!cmd || !delimiter)
		return (0);
	
	// Processa immediatamente l'heredoc
	fd = handle_heredoc_input(shell, delimiter);
	if (fd < 0)
	{
		ft_printf("Error: Failed to handle heredoc input\n");
		return (0);
	}
	
	// Chiudi il file descriptor precedente se esiste
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = fd;
	
	return (1);
}

