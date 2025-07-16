/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:45:25 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/16 17:15:29 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export(t_shell *shell, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (i == 0 && arg[i] != '_' && !ft_isalpha(arg[i]))
		{
			fd_printf(2, "Invalid argument to export\n");
			shell->exit_value = 1;
			return (1);
		}
		else if (i > 0 && arg[i] != '_' && !ft_isalnum(arg[i]))
		{
			fd_printf(2, "Invalid argument to export\n");
			shell->exit_value = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	where_it_goes(t_shell *root, t_cmd *cmd, int i)
{
	while (cmd->argv[i] != NULL)
	{
		if (ft_strchr(cmd->argv[i], '=')
			&& check_export(root, cmd->argv[i]) == 0)
			add_env(root, cmd->argv[i], ENV);
		else if (check_export(root, cmd->argv[i]) == 0)
			add_env(root, cmd->argv[i], EXPORT);
		else if (ft_strchr(cmd->argv[i], '=')
			&& check_export(root, cmd->argv[i]) == 0)
			add_env(root, cmd->argv[i], VAR);
		i++;
	}
}

int	ft_export(t_shell *root, t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		i = 1;
	if (cmd->argc == 1)
	{
		fd = which_fd(root);
		print_env_list_fd(root->env, EXPORT, fd);
		return (0);
	}
	where_it_goes(root, cmd, i);
	return (root->exit_value);
}
