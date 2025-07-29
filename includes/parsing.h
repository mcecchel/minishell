/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:02:45 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/29 14:42:29 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */
typedef enum e_token_type
{
	// PAROLE
	CMD,
	ARG,
	FLAG,
	// OPERATORI DI CONTROLLO
	PIPE,
	// OPERATORI DI REDIREZIONE
	RED_IN,
	RED_OUT,
	APPEND,
	HEREDOC,
	// PARENTESI E SIMBOLI SPECIALI
	QUOTE,
	DQUOTE,
	UNKNOWN,
}			t_token_type;

typedef enum e_var
{
	EXPORT,
	ENV,
	VAR,
}			t_var;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*head;
	struct s_token	*current;
	struct s_token	*next;
	int				is_quoted; // simil buleana: 1 se quoted, 0 se non lo e'
}					t_token;

typedef struct s_cmd
{
	char			*cmd_path;
	char			**argv;
	int				argc;
	int				infile;
	int				outfile;
	int				dummy_on;
	int				pid;
	struct s_cmd	*next;
	char			*heredoc_delimiter;
}					t_cmd;

typedef struct s_env
{
	struct s_env	*prev;
	char			*var;
	char			*arg;
	int				ex_env;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	char	*line;
	t_env	*env;
	t_cmd	*cmd;
	char	**envp;
	int		exit_value;
	t_token	token;
	bool	in_quote;
	int		original_stdin;
	int		original_stdout;
}			t_shell;

typedef struct s_expand_ctx
{
	char		*str;
	int			*i;
	t_shell		*shell;
	char		*result;
	int			initial;
	char		quote;
}	t_expand_ctx;

typedef struct s_extract_ctx
{
	char		quote_char;
	int			start;
	int			end;
	int			quote_type;
	char		*res;
	char		*expanded;
}	t_extract_ctx;

typedef struct s_parse
{
	int		i;
	int		is_first;
	int		waiting;
	t_token	*token_list;
	t_shell	*shell;
	char	*line;
}	t_parse;

// Tokenization functions						tokenizer.c
int				tokenize_input(t_token *token, char **l, t_shell *shell);
int				should_expand_word(t_shell *shell);
const char		*obtain_token_type(t_token *token);

// Token utilities					 			token_utils.c
t_token_type	classify_token(char *str, int is_first_token, int is_quoted);
t_token			*create_token(char *content, t_token_type type, int is_quoted);
void			add_token_to_list(t_token *token_list, t_token *new_token);
void			free_tokens(t_token *token);
t_token			*ft_last(t_token *lst);

// Command parsing								parser.c
t_cmd			*parse_tokens(t_token *token_list, t_shell *shell);
t_cmd			*init_new_cmd(void);
void			add_cmd_to_list(t_cmd **cmd_list, t_cmd *new_cmd);
void			add_argument_to_cmd(t_cmd *cmd, char *arg);
char			*get_cmd_path(t_shell *shell, t_cmd *cmd, char *command);

// Parser utilities and token processing		parser_utils.c
int				handle_redir_token(t_cmd **current, t_cmd **cmd_list,
					t_token **tok, t_shell *shell);
int				process_token(t_token *tok, t_cmd **cmd_list, t_cmd **current,
					t_shell *shell);
int				handle_cmd_advance(t_token **tok, t_cmd **cmd_list,
					t_cmd **current, t_shell *shell);
int				handle_redirection_advance(t_token **tok, t_cmd **cmd_list,
					t_cmd **current, t_shell *shell);
int				handle_standard_advance(t_token **tok, t_cmd **cmd_list,
					t_cmd **current, t_shell *shell);

// Redirection handling							redirection.c
int				setup_input_redir(t_cmd *cmd, char *filename);
int				setup_output_redir(t_cmd *cmd, char *filename, int append);
int				is_redirection_token(t_token_type type);
int				handle_redirection(t_cmd *cmd, t_token *token, t_shell *shell);

//close.c
void			close_cmd_fds(t_cmd *cmd);
void			close_all_cmd_fds(t_cmd *head);
void			close_outfile(t_cmd *cmd);

// Heredoc functions							heredoc.c
char			*expand_heredoc(t_shell *shell, char *line, int exp, int quote);
int				setup_heredoc(t_cmd *cmd, char *delimiter,
					t_shell *shell, int quoted);
bool			should_break(t_shell *shell, char *line, char *delimiter);
int				get_heredoc_content(t_shell *shell, char *delimiter,
					int quoted, int out_fd);

// extract utils								extract.c
char			*extract_word(char *line, int *index, t_shell *shell);
char			*extract_quote(char *line, int *index, int *is_quoted,
					t_shell *shell);
char			*extract_operator(char *line, int *index);

// Heredoc utilities							heredoc_utils.c
void			handle_heredoc_signal(int sig);
void			setup_heredoc_signals(void);
void			restore_signals(void);
char			*create_tmp_heredoc_file(void);

// Variable expansion functions					expansion.c
char			*expand_variables(char *str, t_shell *shell,
					int in_quotes, int initial_parse);
char			*get_env_value(t_shell *shell, char *var_name);
char			*extract_var_name(char *str, int *index);
char			*handle_special_vars(t_shell *shell, char *var_name);
char			*process_variable(t_expand_ctx *ctx);

// Expansion utilities							expansion_utils.c
int				should_expand_in_quotes(int quote_type);
char			*process_literal_text(char *str, int *i, char *result);
char			*append_dollar(t_expand_ctx *ctx);
char			*append_var_value(t_expand_ctx *ctx, char *var_value);
void			advance_var_name(char *str, int *i);

// Additional expansion helpers					expansion_helpers.c
char			*append_substr_to_result(char *str, int start,
					int end, char *res);
char			update_quote_state(char c, char curr);
char			*append_char(char *result, char c);
char			*process_loop(t_expand_ctx *ctx);
int				handle_token_in_loop(t_token **tok, t_cmd **cmd_list,
					t_cmd **current, t_shell *shell);

// Environment handling							environment.c
char			*find_env_path(t_shell *shell);
char			**get_paths(t_shell *shell);
void			update_shell_envp(t_shell *shell);

// Command execution							execution.c
void			execute_cmd(t_shell *shell, t_cmd *cmd);
void			execute_command_list(t_shell *shell);
void			cleanup_shell(t_shell *shell);

// Execution utilities							execution_utils.c
void			fork_error_handler(t_shell *shell, t_cmd *cmd,
					int err, int exit_code);
int				is_directory(char *path);
void			execve_failed(t_shell *shell, t_cmd *cmd, char *path);
void			print_envp_char(char **envp);
char			*search_command(char **paths, char *cmd);

// Pipeline utilities							pipeline.c
void			wait_for_children_safe(t_cmd *cmd_list, t_shell *shell);
int				handle_pipe_creation(t_cmd *current, int *fd_pipe);
int				update_prev_pipe(t_cmd *current, int *fd_pipe, int prev_pipe);

// Command management							dummy.c
int				is_dummy_command(t_cmd *cmd);
void			free_single_cmd(t_cmd *cmd);
void			merge_dummy_to_real(t_cmd *dummy, t_cmd *real);
t_cmd			*remove_dummy_from_list(t_cmd *cmd_list, t_cmd *to_remove);
t_cmd			*optimize_command_list(t_cmd *cmd_list);

// Shell core functions							shell_core.c
int				read_and_validate_line(t_shell *shell);
int				handle_tokenization(t_shell *shell);
int				handle_parsing(t_shell *shell);
void			handle_builtin_or_exec(t_shell *shell);
void			copy_system_envp_to_shell(char **system_envp, t_shell *shell);

// I/O management								io_management.c
void			restore_stdio(t_shell *shell);
void			redirect_stdio(t_cmd *cmd);
void			sigint_handler(int sig);
void			debug_cmds(t_cmd *cmd_list);

//Command_handler.c
int				handle_arg_flag_token(t_cmd **current,
					t_cmd **cmd_list, t_token *tok);
void			handle_dummy_in_token(t_cmd **cur, t_token **tok);
int				handle_cmd_token(t_cmd **cmd_list, t_cmd **cur,
					t_token **tok, t_shell *sh);
int				handle_pipe_token(t_token *token, t_cmd **current,
					t_cmd **cmd_list, t_shell *shell);
t_cmd			*create_base_cmd(t_token *token);

//content_parser.h
char			*get_content(char *line, int *i,
					int *is_quoted, t_shell *shell);
char			*get_next_piece(char *line, int *i,
					int *quoted, t_shell *shell);
char			*append_content(char *content, char *tmp);
void			update_state(t_token_type type, int *is_first, int *waiting);
void			expand_or_not(t_extract_ctx *ctx, t_shell *shell);

//shell_core_1.c
void			init_shell(t_shell *shell);
bool			is_builtin(char *cmd);
void			status_code_update(t_shell *shell);
int				parser_builtin(t_shell *root, t_cmd *cmd);
void			new_exit_code(t_shell *shell, int status);

//tokenizer_1.c
int				process_tokens(t_parse *p);
int				handle_operator(t_parse *p);
int				add_operator_token(t_parse *p, char *op);
int				handle_content(t_parse *p);
int				add_content_token(t_parse *p, char *content, int is_quoted);

//pipeline_main.c
int				process_command_loop(t_shell *shell, t_cmd *current,
					int *prev_pipe);
int				handle_fork_creation(t_cmd *current);
void			setup_child_process(t_cmd *current,
					int prev_pipe, int *fd_pipe);
void			setup_parent_process(int prev_pipe,
					int *fd_pipe, t_cmd *current);
int				handle_standard_advance(t_token **tok, t_cmd **cmd_list,
					t_cmd **current, t_shell *shell);

// String and general utilities					utils.c
void			free_matrix(char **str);
void			free_cmd_list(t_cmd *cmd);
void			debug_tokens(t_token *token);
int				is_valid_command(t_cmd *cmd, char *command);

//utils_1.c
bool			is_special(char c);
bool			is_quote(char c);
char			*surround_with_quotes(char *str);
void			find_closing_quote(t_extract_ctx *ctx, char *line);
int				is_preceded_by_heredoc(char *str, int i);

#endif
