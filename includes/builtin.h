/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:54:11 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/30 16:51:25 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"

//copy_free_env
t_env			*create_env_node(char *env_str);
void			append_env_node(t_env **head, t_env **current, t_env *new_node);
void			add_oldpwd_node(t_env **head, t_env **current);
t_env			*copy_env(char **env);
void			free_env_list(t_env *env);

//cd
t_env			*find_env(t_env *env, char *to_change);
void			change_env(t_shell *root, char *old_path, char *current_path);
char			*get_target_path(t_shell *root);
int				change_directory(const char *target_path);
int				ft_cd(t_shell *root, t_cmd *cmd);

//echo
int				only_char(const char *str, int a, int b, char flag);
int				which_arg(t_cmd *cmd);
int				ft_echo(t_shell *shell, t_cmd *cmd);

//exit
void			goodbye_my_dear(t_shell *root);
void			clean_exit(t_shell *root);
void			too_many_args(t_shell *root, t_cmd *cmd, int len);
void			ft_exit(t_shell *root, t_cmd *cmd);

//ft_export
int				is_valid_export_identifier(char *arg);
int				check_export(t_shell *shell, char *arg, int print);
void			where_it_goes(t_shell *root, t_cmd *cmd, int i);
int				ft_export(t_shell *root, t_cmd *cmd);

//pwd
int				ft_pwd(t_shell *shell, t_cmd *cmd);

//unset
int				ft_unset(t_shell *shell, t_cmd *cmd);

//sort_env
void			swap_env_content(t_env *a, t_env *b);
t_env			*sort_env_list(t_env *m_env);

//utils_builtin
char			*ft_strjoin_free_s2(char *s1, char *s2);
void			print_env_list_fd(t_env *env, int what, int fd);
long long int	ft_atoi_ll(const char *nptr);
int				which_fd(t_shell *shell);
void			copy_system_envp_to_shell(char **system_envp, t_shell *shell);

//utils_env
int				update_env(t_env *env, char *name, char *value, int type);
void			add_new_env(t_shell *root, char *name, char *value, int type);
char			*extract_name(char *arg, int *equal_pos);
char			*extract_value(char *arg, int equal_pos, char *name);
void			add_env(t_shell *root, char *arg, int type);

//utils_matrix_env
int				count_env_list(t_env *env);
char			*create_env_string(t_env *env_node);
int				fill_env_matrix(char **envp, t_env *env, int count);
char			**env_list_to_matrix(t_env *env);
void			update_shell_envp(t_shell *shell);

#endif
