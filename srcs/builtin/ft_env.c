/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:40:04 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/19 23:59:06 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell root)
{
	int i;

	i = 0;
	while (root.env[i] != NULL)
	{
		ft_printf("declare -x ");
		ft_printf("%s\n", root.env[i]);
		i++;
	}
}
