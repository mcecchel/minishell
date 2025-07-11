/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:39:49 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/11 15:26:15 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_arg(t_shell *shell)
{
	if(ft_strcmp(shell->cmd->argv[0], "echo") == 0 
		&& ft_strncmp(shell->cmd->argv[1], "-n", 2) == 0
		&& ft_strcmp(shell->cmd->argv[1], "n") == 0)
		return(3);
	return (1);
}

int	ft_echo(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		fd;

	if (!shell || !(cmd->argc > 1) || !cmd->argv)
		return (1);
	i = which_arg(shell);
	fd = which_fd(shell);
	while (cmd->argv[i] != NULL)
	{
		if (i > 1 && shell->token.type != QUOTE)
			write(fd, " ", 1);
		fd_printf(fd, cmd->argv[i]);
		i++;
	}
	if(which_arg(shell) != 2)
		write(fd, "\n", 1);
	return (0);
}
