/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:38:22 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 18:06:31 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_path(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->var && ft_strcmp(env->var, "PATH") == 0)
			return (env->arg);
		env = env->next;
	}
	return (NULL);
}

char	**get_paths(t_shell *shell)
{
	char	*path_env;
	char	**paths;

	path_env = find_env_path(shell);
	if (!path_env)
	{
		perror("Error: Failed to find path");
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		perror("Error: Failed to split path");
	return (paths);
}
