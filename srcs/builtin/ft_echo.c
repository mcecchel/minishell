/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:39:49 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/15 17:41:29 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_char(const char *str, int a, int b, char flag)
{
	int	i;

	i = a;
	if (!str || a < 0 || b < a)
		return (0);
	while (i <= b && str[i] != '\0')
	{
		if (str[i] != flag)
			return (0);
		i++;
	}
	return (1);
}

int	which_arg(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd || !cmd->argv)
		return (1);
	while (cmd->argv[i] && cmd->argv[i][0] == '-' && only_char(cmd->argv[i],
		1, ft_strlen(cmd->argv[i]), 'n') && cmd->argv[i][1] == 'n')
		i++;
	return (i);
}

int	ft_echo(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	fd;
	int	n_flag;

	if (!shell || !cmd || !cmd->argv)
		return (1);
	i = which_arg(cmd);
	n_flag = (i > 1);
	fd = which_fd(shell);
	while (cmd->argv[i])
	{
		if (i > which_arg(cmd))
			write(fd, " ", 1);
		write(fd, cmd->argv[i], ft_strlen(cmd->argv[i]));
		i++;
	}
	if (!n_flag)
		write(fd, "\n", 1);
	return (0);
}
