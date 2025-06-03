/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:59:36 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/03 18:25:43 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free_s2(char *s1, char *s2)
{
	int				is1;
	int				is2;
	unsigned char	*l;

	is1 = 0;
	is2 = 0;
	if (!s1)
		return (s2);
	l = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!l)
		return (NULL);
	while (s1[is1])
	{
		l[is1] = s1[is1];
		is1++;
	}
	;
	while (s2[is2])
	{
		l[is1 + is2] = s2[is2];
		is2++;
	}
	free(s2);
	return ((char *)l);
}

void	print_env_list(t_env *env, bool is_env)
{
	while (env && is_env)
	{
		if (env->ex_env == 1)
		{
			ft_printf("%s=", env->var);
			if (env->arg)
				ft_printf("%s\n", env->arg);
		}
		//ft_printf("EXPORTED: %d\n", env->ex_env);
		env = env->next;
	}
	while (env && !is_env)
	{
		ft_printf("declare -x ");
		ft_printf("%s=", env->var);
		if (env->arg)
			ft_printf("%s\n", env->arg);
		if (!env->arg)
			ft_printf("\n");
		//ft_printf("EXPORTED: %d\n", env->ex_env);
		env = env->next;
	}
}
