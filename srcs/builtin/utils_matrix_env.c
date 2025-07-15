/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_matrix_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:58:05 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/15 18:02:40 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_env_list(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		if (current->ex_env == ENV && current->arg)
			count++;
		current = current->next;
	}
	return (count);
}

static char	*create_env_string(t_env *env_node)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(env_node->var, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, env_node->arg);
	free(temp);
	return (result);
}

static int	fill_env_matrix(char **envp, t_env *env, int count)
{
	t_env	*current;
	int		i;

	current = env;
	i = 0;
	while (current && i < count)
	{
		if (current->ex_env == ENV && current->arg)
		{
			envp[i] = create_env_string(current);
			if (!envp[i])
				return (0);
			i++;
		}
		current = current->next;
	}
	return (1);
}

char	**env_list_to_matrix(t_env *env)
{
	char	**envp;
	int		count;

	if (!env)
		return (NULL);
	count = count_env_list(env);
	envp = ft_calloc(sizeof(char *), (count + 1));
	if (!envp)
		return (NULL);
	if (!fill_env_matrix(envp, env, count))
		return (free_matrix(envp), NULL);
	return (envp);
}

void	update_shell_envp(t_shell *shell)
{
	char	**new_envp;

	if (!shell || !shell->env)
		return ;
	if (shell->envp)
		free_matrix(shell->envp);
	new_envp = env_list_to_matrix(shell->env);
	shell->envp = new_envp;
}
