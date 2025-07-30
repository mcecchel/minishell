/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:59:36 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/30 16:48:24 by mbrighi          ###   ########.fr       */
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
	while (s2[is2])
	{
		l[is1 + is2] = s2[is2];
		is2++;
	}
	free(s2);
	return ((char *)l);
}

void	print_env_list_fd(t_env *env, int what, int fd)
{
	while (env && what == ENV)
	{
		if (env->ex_env == 1)
		{
			fd_printf(fd, "%s", env->var);
			if (env->arg)
				fd_printf(fd, "=%s\n", env->arg);
		}
		env = env->next;
	}
	while (env && what == EXPORT)
	{
		if (env->ex_env != VAR)
		{
			fd_printf(fd, "declare -x ");
			fd_printf(fd, "%s", env->var);
			if (env->arg)
				fd_printf(fd, "=\"%s\"\n", env->arg);
			if (!env->arg)
				fd_printf(fd, "\n");
		}
		env = env->next;
	}
}

long long int	ft_atoi_ll(const char *nptr)
{
	long long int	sign;
	long long int	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

int	which_fd(t_shell *shell)
{
	int	fd;

	if (shell->cmd->outfile != -1)
		fd = shell->cmd->outfile;
	else
		fd = 1;
	return (fd);
}

void	copy_system_envp_to_shell(char **system_envp, t_shell *shell)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (system_envp[count])
		count++;
	shell->envp = ft_calloc(count + 1, sizeof(char *));
	if (!shell->envp)
		return ;
	while (i < count)
	{
		shell->envp[i] = ft_strdup(system_envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
}
