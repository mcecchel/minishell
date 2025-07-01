/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:39:49 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/01 13:54:36 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *shell)
{
	int	i;

	i = 1;
	if (shell->token.type != PIPE && shell->token.type != RED_IN
		&& shell->token.type !=  RED_OUT)
	while (shell->cmd->argv[i] != NULL)
	{
		fd_printf(1, shell->cmd->argv[i]);
		write(1, " ", 1);
		i++;
	}
	write(1, "\b", 1);
	write(1, "\n", 1);
	ft_putnbr_fd(1, shell->cmd->argc);
	write(1, "\n", 1);
}
