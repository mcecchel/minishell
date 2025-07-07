/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:39:49 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/07 18:00:24 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_arg(t_shell *shell)
{
	if(ft_strcmp(shell->cmd->argv[0], "echo") == 0 
		&& ft_strcmp(shell->cmd->argv[0], "-n") == 0)
		return(2);
	return (1);
}

int	ft_echo(t_shell *shell)
{
	int		i;
	int		fd;
	char	*line;

	i = which_arg(shell);
	fd = which_fd(shell);
	if (shell->cmd->argv[1] == NULL && shell->cmd->infile != -1)
	{
		while ((line = get_next_line(shell->cmd->infile)) != NULL)
		{
			write(fd, line, ft_strlen(line));
			free(line);
		}
		return (0);
	}
	while (shell->cmd->argv[i] != NULL)
	{
		if (i > 1)
			write(fd, " ", 1);
		fd_printf(fd, shell->cmd->argv[i]);
		i++;
	}
	if(shell->token.type != FLAG)
		write(fd, "\n", 1);
	return (0);
}
