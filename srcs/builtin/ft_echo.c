/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:39:49 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/04 17:00:14 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	open_file(t_shell *shell)
// {
	

// }


int	ft_echo(t_shell *shell)
{
	int	i;
	//int	fd;

	i = 1;
	if (shell->token.type != PIPE && shell->token.type != RED_IN
		&& shell->token.type !=  RED_OUT)
	// 	fd = 1;
	// else
	// 	fd = open_file(shell);
	while (shell->cmd->argv[i] != NULL)
	{
		if(i > 1)
			write(1, " ", 1);
		fd_printf(1, shell->cmd->argv[i]);
		i++;
	}
	write(1, "\n", 1);
	return (0);
}
