/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:31:11 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/06 14:38:55 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_env_content(t_env *a, t_env *b)
{
	char	*tmp_var;
	char	*tmp_arg;
	int		tmp_ex;

	tmp_var = a->var;
	tmp_arg = a->arg;
	tmp_ex = a->ex_env;
	a->var = b->var;
	a->arg = b->arg;
	a->ex_env = b->ex_env;
	b->var = tmp_var;
	b->arg = tmp_arg;
	b->ex_env = tmp_ex;
}

t_env	*sort_env_list(t_env *m_env)
{
	t_env	*current;
	int		sorted;

	if (!m_env)
		return (NULL);
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		current = m_env;
		while (current->next)
		{
			if (ft_strcmp(current->var, current->next->var) > 0)
			{
				swap_env_content(current, current->next);
				sorted = 0;
			}
			current = current->next;
		}
	}
	return (m_env);
}
