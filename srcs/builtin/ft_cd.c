/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:22:07 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/15 17:31:31 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = malloc(num * size);
	i = 0;
	if (!ptr)
		return (NULL);
	while (i < num * size)
	{
		ptr[i] = '\0';
		i++;
	}
	return ((void *)ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	str = ft_calloc(sizeof(char), (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			j = 1;
			while ((i + j) < len && (little[j] != '\0') \
			&& (big[i + j] == little[j]))
				j++;
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

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

void	change_env(char **mini_env, char *old_path, char *current_path)
{
	int i;

	i = 0;
	while (mini_env[i])
	{
		if (ft_strnstr(mini_env[i], "PWD=", 4) != 0)
		{
			free (mini_env[i]);
			mini_env[i] = ft_strdup(current_path);
			break;
		}
		i++;
	}
	i = 0;
	while (mini_env[i])
	{
		if (ft_strnstr(mini_env[i], "OLDPWD=", 7) != 0)
		{
			free (mini_env[i]);
			mini_env[i] = ft_strdup(old_path);
			break;
		}
		i++;
	}
}

int	ft_cd(char *new_path, char **mini_env)
{
	char	*current_path;
	char	*old_path;

	old_path = getcwd(NULL, 0);
	old_path = ft_strjoin_free_s2("OLDPWD=", old_path);
	//aggiorna una variabile d'appoggio che tiene l'oldpwd per ritornare in quella directory se viene usato cd -
	if (chdir(new_path) == -1)
	{
		perror("cd");
		free(old_path);
		return (1);
	}
	current_path = getcwd(NULL, 0);
	current_path = ft_strjoin_free_s2("PWD=", current_path);
	if (new_path[0] == '-' && new_path[1] == '\0')
		current_path = old_path;
	change_env(mini_env, old_path, current_path);
	printf("Old path: %s\n", old_path);
	printf("Current path: %s\n", current_path);
	free(current_path);
	free(old_path);
	return(0);
}

void	free_matrix_error(char **mini_envp, int i)
{
	int index;

	index = 0;
	while (index < i)
	{
		free(mini_envp[index]);
		index++;
	}
	free(mini_envp);
	perror("Failed to duplicate envp");
}

void	free_matrix(char **mini_envp)
{
	int index;
	int	i;

	index = 0;
	i = 0;
	while (mini_envp[i] != NULL)
		i++;
	while (index < i)
	{
		free(mini_envp[index]);
		index++;
	}
	free(mini_envp);
}

char	**copy_env(char **env)
{
	size_t	count;
	size_t	i;
	char	**mini_env;

	count = 0;
	i = 0;
	while (env[count] != NULL)
		count++;
	mini_env = ft_calloc((count + 1), sizeof(char *));
	if (!mini_env)
	{
		perror("malloc");
		return (NULL);
	}
	while (i < count)
	{
		mini_env[i] = ft_strdup(env[i]);
		if (!mini_env[i])
		{
			free_matrix_error(mini_env, i);
			return (NULL);
		}
		i++;
	}
	return (mini_env);
}

void	print_env(char **mini_env)
{
	int i = 0;
	while (mini_env[i] != NULL)
	{
		printf("%s\n", mini_env[i]);
		i++;
	}
}

int main(int argc, char **argv, char **envp)
{
	char	**mini_env;
	int 	i;
	int		k;

	i = 0;
	k = 0;
	mini_env = copy_env(envp);
	//print_env(mini_env);
	ft_cd("Libft/ft_printf", mini_env);
	ft_cd(argv[1], mini_env);
	printf("//////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
	//print_env(mini_env);
	free_matrix(mini_env);
	return(0);
}
