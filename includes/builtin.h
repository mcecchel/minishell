/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:11 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/21 18:19:17 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"

//cd

//copy_free_env
t_env	*create_env_node(char *env_str);
t_env	*copy_env(char **env);
void	append_env_node(t_env **head, t_env **current, t_env *new_node);
void	free_env_list(t_env *env);

//ft_export

//env

//pwd

//unset
void	ft_unset(t_env **head, char *var_name);

//utils builtin
char	*ft_strjoin_free_s2(char *s1, char *s2);
void	print_env_list(t_env *env);

//sort_env
void	swap_env_content(t_env *a, t_env *b);
void	sort_env_list(t_env *m_env);



#endif
