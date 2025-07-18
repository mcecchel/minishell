/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:53:30 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/19 13:39:59 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Configurazione segnali per heredoc
void	handle_heredoc_signal(int sig)
{
	(void)sig;
	current_child_pid = sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, handle_heredoc_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
