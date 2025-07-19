/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:58:47 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/19 15:15:27 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_heredoc(t_shell *shell, char *line, int exp, int quote)
{
	char	*expanded_line;
	char	*res;

	if (!line)
		return (NULL);
	if (exp && quote != 1)
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

int	handle_heredoc_input(t_shell *shell, char *delimiter, int quoted)
{
	char	*line;
	char	*tmp_file;
	int		fd;
	char	*expanded_line;
	int		ret_fd;

	tmp_file = create_tmp_heredoc_file();
	if (!tmp_file)
		return (-1);
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error: Failed to open heredoc file");
		free(tmp_file);
		return (-1);
	}
	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		status_code_update(shell);
		if (shell->exit_value == 130)
		{
			close(fd);
			unlink(tmp_file);
			free(tmp_file);
			return (-3);
		}
		if (!line)
		{
			ft_printf("\nminishell: warning: here-document delimited"
				" by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = expand_heredoc(shell, line, 1, quoted);
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
	free(tmp_file);
	return (ret_fd);
}

int	setup_heredoc(t_cmd *cmd, char *delimiter, t_shell *shell, int quoted)
{
	int	fd;

	if (!delimiter)
		return (0);
	fd = handle_heredoc_input(shell, delimiter, quoted);
	if (fd < 0)
	{
		if (fd == -1)
			fd_printf(2, "Error: Failed to handle heredoc input\n");
		return (fd == -2);
	}
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = fd;
	return (1);
}
