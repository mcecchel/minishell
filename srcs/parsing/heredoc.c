/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:58:47 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/19 19:47:19 by mbrighi          ###   ########.fr       */
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
		expanded_line = expand_variables(line, shell, 0, 0);
	else
		expanded_line = ft_strdup(line);
	free(line);
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

static bool	should_break(t_shell *shell, char *line, char *delimiter)
{
	if (!line)
	{
		ft_printf("\nminishell: warning: here-document delimited"
			" by end-of-file (wanted `%s')\n", delimiter);
		return (true);
	}
	if (shell->exit_value == 130)
		return (free(line), true);
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (true);
	}
	return (false);
}

int	get_heredoc_content(t_shell *shell, char *delimiter, int quoted, int out_fd)
{
	char	*line;

	setup_heredoc_signals();
	while (true)
	{
		line = readline("> ");
		status_code_update(shell);
		if (should_break(shell, line, delimiter))
			break ;
		line = expand_heredoc(shell, line, 1, quoted);
		if (line)
			write(out_fd, line, ft_strlen(line));
		free(line);
	}
	return (0);
}

int	setup_heredoc(t_cmd *cmd, char *delimiter, t_shell *shell, int quoted)
{
	int		fd;
	char	*file;

	if (!delimiter)
		return (0);
	file = create_tmp_heredoc_file();
	if (!file)
		return (-1);
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("Error: Failed to open heredoc file"), free(file), -1);
	if (shell->exit_value != 130)
		get_heredoc_content(shell, delimiter, quoted, fd);
	close(fd);
	if (cmd->infile != -1)
		close(cmd->infile);
	cmd->infile = open(file, O_RDONLY);
	unlink(file);
	if (cmd->infile < 0)
		return (perror("Error: Failed to open heredoc file"), free(file), -1);
	return (free(file), 1);
}
