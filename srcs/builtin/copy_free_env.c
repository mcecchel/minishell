/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_free_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:57:36 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/19 23:56:51 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix_error(char **mini_envp, int i)
{
	int index;

	index = 0;
	while (index < i)
	{
		free(mini_envp[index]);
		index++;
	}
	free(mini_envp);
	perror("Failed to duplicate envp");
}

void	free_matrix(char **mini_envp)
{
	int index;
	int	i;

	index = 0;
	i = 0;
	while (mini_envp[i] != NULL)
		i++;
	while (index < i)
	{
		free(mini_envp[index]);
		index++;
	}
	free(mini_envp);
}

char	**copy_env(char **env, t_shell root)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (env[count] != NULL)
		count++;
	root.env = ft_calloc((count + 1), sizeof(char *));
	if (!root.env)
	{
		perror("malloc");
		return (NULL);
	}
	while (i < count)
	{
		root.env[i] = ft_strdup(env[i]);
		if (!root.env[i])
		{
			free_matrix_error(root.env, i);
			return (NULL);
		}
		i++;
	}
	return (root.env);
}

