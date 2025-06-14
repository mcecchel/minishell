/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:54:32 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/06 14:37:35 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	size_t	pwd_len;
	char	*pwd;

	pwd_len = 4096;
	pwd = (char *)ft_calloc(1, pwd_len);
	if (getcwd(pwd, pwd_len) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	else
		write(1, pwd, pwd_len);
	write (1, "\n", 1);
	free(pwd);
	return (0);
}
