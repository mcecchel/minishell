/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:59:36 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/19 17:04:43 by mbrighi          ###   ########.fr       */
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

void	sort_env(char **mini_env)
{
	int rows;
	int col;
	int count;
	char *temp;

	rows = 0;
	count = 0;
	while (mini_env[count] != NULL)
		count++;
	while (rows < count - 1)
	{
		col = 0;
		while (col < count - rows - 1)
		{
			if (ft_strcmp(mini_env[col], mini_env[col + 1]) > 0)
			{
				temp = mini_env[col];
				mini_env[col] = mini_env[col + 1];
				mini_env[col + 1] = temp;
			}
			col++;
		}
		rows++;
	}
}
