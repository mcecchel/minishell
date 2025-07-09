/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:11 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/09 16:40:22 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"

int				parser_builtin(t_shell *root);

//cd
t_env 			*find_env(t_env *env, char *to_change);
void			change_env(t_shell *root, char *old_path, char *current_path);
int				ft_cd(t_shell *root);

//copy_free_env
t_env			*create_env_node(char *env_str);
t_env			*copy_env(char **env);
void			append_env_node(t_env **head, t_env **current, t_env *new_node);
void			free_env_list(t_env *env);
void			add_node(t_env **head, t_env **current, char str, int ex_env);

//ft_export
void			add_env(t_shell *root, char *arg, int type);
void			ft_export(t_shell *root);

//exit
void			ft_exit(t_shell *root);
void			clean_exit(t_shell *root);

//pwd
int				ft_pwd(t_shell *shell);

//unset
int			ft_unset(t_shell *shell);

//utils builtin
char			*ft_strjoin_free_s2(char *s1, char *s2);
void			print_env_list(t_env *root, int what);
void			print_env_list_fd(t_env *env, int what, int fd);
long long int	ft_atoi_ll(const char *nptr);

//sort_env
void			swap_env_content(t_env *a, t_env *b);
t_env			*sort_env_list(t_env *m_env);

//echo
int				ft_echo(t_shell *shell);

#endif
