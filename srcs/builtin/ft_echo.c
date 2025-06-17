/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:39:49 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/17 16:47:29 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->token.type != PIPE && shell->token.type != RED_IN
		&& shell->token.type !=  RED_OUT)
	while (shell->cmd->argv[i] != NULL)
	{
		fd_printf(1, shell->cmd->argv[i]);
		i++;
	}
}
