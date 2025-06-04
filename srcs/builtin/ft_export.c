/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:45:25 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/04 17:20:35 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_env(t_shell *root, char *arg, bool is_env)
{
	t_env *new_env;
	char *name;
	char *value;
	int i;

	new_env = root->env;
	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_substr(arg, 0, i);
	if (arg[i] == '=')
		value = ft_strdup(arg + i + 1);
	else
		value = NULL;
	new_env = ft_calloc(1, sizeof(t_env));
	new_env->var = name;
	new_env->arg = value;
	new_env->ex_env = 1;
	if (!is_env)
		new_env->ex_env = 0;
	new_env->next = root->env;
	if (root->env)
		root->env->prev = new_env;
	new_env = sort_env_list(new_env);
	root->env = new_env;
}

void ft_export(t_shell *root, char *args)
{
	if (!args)
	{
		print_env_list(root->env, false);
		return;
	}

	if (ft_strchr(args, '='))
		add_env(root, args, true);
	else
		add_env(root, args, false);
}

