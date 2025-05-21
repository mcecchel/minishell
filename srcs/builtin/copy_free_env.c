/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_free_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:57:36 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/21 18:32:46 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(char *env_str)
{
	t_env	*node;
	char	*equal;

	node = ft_calloc(sizeof(t_env), 1);
	if (!node)
		return (NULL);
	equal = ft_strchr(env_str, '=');
	if (equal)
	{
		node->var = ft_substr(env_str, 0, equal - env_str);
		node->arg = ft_strdup(equal + 1);
		node->ex_env = 1;
	}
	else
	{
		node->var = ft_strdup(env_str);
		node->arg = NULL;
	}

	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	append_env_node(t_env **head, t_env **current, t_env *new_node)
{
	if (!*head)
		*head = new_node;
	else
	{
		(*current)->next = new_node;
		new_node->prev = *current;
	}
	*current = new_node;
}

t_env	*copy_env(char **env)
{
	t_env	*head = NULL;
	t_env	*current = NULL;
	t_env	*new_node;
	int		i;

	i = 0;
	while (env[i])
	{
		new_node = create_env_node(env[i]);
		if (!new_node)
			return (NULL); // gestione errore reale consigliata
		append_env_node(&head, &current, new_node);
		i++;
	}
	if(head)
		sort_env_list(head);
	return (head);
}

void	free_env_list(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env->next;
		free(env->var);
		free(env->arg);
		free(env);
		env = tmp;
	}
}
