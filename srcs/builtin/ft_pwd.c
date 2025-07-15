/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:54:32 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/15 17:41:07 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, t_cmd *cmd)
{
	size_t	pwd_len;
	char	*pwd;
	int		fd;

	(void)cmd;
	fd = which_fd(shell);
	pwd_len = 4096;
	pwd = (char *)ft_calloc(1, pwd_len);
	if (getcwd(pwd, pwd_len) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	else
		write(fd, pwd, ft_strlen(pwd));
	write (fd, "\n", 1);
	free(pwd);
	return (0);
}
