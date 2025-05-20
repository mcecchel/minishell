/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:11 by mbrighi           #+#    #+#             */
/*   Updated: 2025/05/20 13:52:54 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"

//cd
void	change_env(t_shell root, char *old_path, char *current_path);
int		ft_cd(char *new_path, t_shell root);

//copy_free_env
void	free_matrix_error(char **mini_envp, int i);
void	free_matrix(t_shell root);
char	**copy_env(char **env, t_shell root);

//ft_export
void 	ft_export(t_shell root, char *s);

//env
void	ft_env(t_shell root);

//pwd
int		ft_pwd();

//unset
void	ft_unset(char *to_remove, t_shell root);

//utils builtin
char	*ft_strjoin_free_s2(char *s1, char *s2);
void	sort_env(t_shell root);

#endif
