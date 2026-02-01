/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copito <copito@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:12:29 by copito            #+#    #+#             */
/*   Updated: 2025/07/31 14:05:33 by copito           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include "utils/utils.h"

# define PROMPT  "\033[31mサ »\033[0m " 

// Global variable for exit status (?)
extern int	g_exit_status;

typedef struct dir_info
{
	char	dir[4096];
	char	*prev_dir;
}	t_dir_info;

typedef struct env
{
	char	**env_dup;
	char	**vars;
}	t_envp;

typedef struct var
{
	char	*name;
	char	*value;
}	t_var;

typedef struct s_quote_data
{
	char	*cmd;
	int		*i;
	char	*tmp;
	int		*j;
}	t_quote_data;

typedef struct s_pipe_data
{
	char		**cmd_parts;
	int			check;
	int			prev_fd;
	int			fd[2];
	char		**envp;
	t_dir_info	*dir;
	t_envp		*envp_d;
}	t_pipe_data;

typedef struct s_pipe_params
{
	char		**envp;
	t_dir_info	*dir;
	t_envp		*envp_d;
}	t_pipe_params;

typedef struct s_exec_ctx
{
	char		**envp;
	t_dir_info	*dir;
	t_envp		*envp_d;
}	t_exec_ctx;

// ERROR
void		msg(char *str);
void		fork_fail(char **cmds, int pid);
void		free_var(t_var *var);
int			memory_error(void);

// ENV_PWD
char		*lookinenv(char **envp, char *lookfor);
void		update_shlvl(char **envp);
t_dir_info	*my_pwd(char **envp);
int			show_env(char **envp);
void		update_env(char **envp, t_dir_info *dir);

// MATRIX
char		**dupmatrix(char **og);
void		matrixfree(char	**matrix);
void		free_arraymatrix(char *array, char **matrix);
void		print_matrix(char **matrix);
int			sizematrix(char **matrix);

// PATHS
void		parse_path(char *path, char **cmds, char **envp);
char		*getpatharray(char **envp);

// EXECT
void		to_exec(char *cmd, char **envp);
void		execution(char *path, char **cmds, char **envp);
void		builtin_exec(char *cmd, char **args, t_exec_ctx *ctx);

// PROMPT
int			prompt(t_envp *envp_d);

// QUOTES
char		*check_quotes(char *cmd, t_envp *envp_d);
char		*get_variable(char *cmd, t_envp *envp_d);
void		init_quote_data(char *cmd, char *tmp, t_quote_data *data);
char		*remove_quotes_from_cmd(char *cmd, t_envp *envp_d);
char		*quotes_actions(char *cmd, int i_double, int i_single,
				t_envp *envp_d);
int			expand_variable_in_quotes(char *cmd, int *i,
				t_envp *envp_d, char **variable);
char		*expand_double_quote_variable(t_quote_data *data, t_envp *envp_d);
char		*handle_variable_expansion(t_quote_data *data, char quote,
				t_envp *envp_d);
void		handle_exit_status_expansion(char *tmp, int *j, int *i);
char		*copy_var_to_buff(char *tmp, int *j,
				char *variable, int cmd_len);
char		*process_quoted_content(t_quote_data *data, char quote,
				t_envp *envp_d);
char		*process_quote_section(t_quote_data *data, t_envp *envp_d);
int			process_unquoted_content(t_quote_data *data, t_envp *envp_d);
//(muy larga y muchos argumentos)
char		*copy_literal_in_single_quotes(t_quote_data *data, char quote);
//void		handle_normal_character(char *cmd, char *tmp, int *i, int *j);

// PARSER
void		parser(t_dir_info *dir, char **envp, char *cmd, t_envp *envp_d);
int			check_builtins(char *cmd);
void		sendto_builtin(char **cmds, t_dir_info *dir,
				char **envp, t_envp *envp_d);
int			check_pipe(char *cmd);
int			parse_redirections(char *cmd);

// PIPELINE
void		pipeline(char *cmd, char **envp, t_dir_info *dir, t_envp *envp_d);
void		do_redirections(char **cmd_parts, char **envp,
				t_dir_info *dir, t_envp *envp_d);
void		handle_last_command(int prev_fd, char *cmd, t_pipe_params *params);

// PIPEAUX
int			pipe_process(char **cmds, t_pipe_params *params, int prev_fd);
void		handle_child_process(t_pipe_data *data);
void		setup_child_redirections(t_pipe_data *data);
void		execute_child_command(t_pipe_data *data);

// REDIRECTIONS
void		handle_redirections(char **cmds);
void		handle_append_redirection(char **cmds, int i);
void		handle_heredoc_redirection(char **cmds, int i);
void		handle_input_redirection(char **cmds, int i);
void		handle_output_redirection(char **cmds, int i);
int			read_and_check_delimiter(int pipe_fd, char *delimiter);
void		setup_heredoc_input(int pipe_fd[2]);

// REDIRECTIONS_AUX
void		execute_with_redirections(char *cmd, char **envp,
				t_dir_info *dir, t_envp *envp_d);
char		**normalize_redirections(char *cmd);
void		son_proccess(char **cmds, char **envp,
				t_dir_info *dir, t_envp *envp_d);
void		free_extra_token(char **cmds, int i, int seen_redirection);
int			check_end_of_token(char *cmd, int i);

// REDIRECTIONS_PARSING
int			count_tokens(char *cmd);
int			count_total_tokens(char **cmds);
int			extract_operator_or_token(char *cmd, int i, char **result, int j);
int			check_redirection_syntax(char **cmds);
int			process_redirection_token(char **cmds, int i);

// CD_ECHO
void		my_cd(char **cmds, char **envp, t_dir_info *dir);
void		my_echo(char **cmds, t_envp *envp_d);
int			echo_quotes(char *cmd);
void		echo_smth(char **cmds, int i, t_envp *envp_d);
int			echo_nothing(char **cmds);

// VARIABLES
void		check_variables(char *cmd, t_envp *envp_d);

// VARIABLES_AUX
char		*extract_value(char *cmd);
char		*extract_name(char *cmd);
int			var_no_null(t_var *var, t_envp *envp_d);
int			is_variable_assignment(char *cmd);
int			check_var_name(char *var_name);

// EXPORT
int			export_variable(char *cmd, t_envp *envp_d);
void		delete_var(t_envp *envp_d, t_var *var);
int			export_dup(t_envp *envp_d, t_var *var);
int			export_var(t_envp *envp_d, t_var *var);
void		free_dup(t_envp *envp_d, char **aux);

// EXPORT_AUX
void		add_dup(t_envp *envp_d, t_var *var);
void		export_no_equal(t_envp *envp_d, char *cmd);
// EXIT STATUS
void		set_exit_status(int status);
int			get_exit_status(void);
char		*expand_exit_status(char *str);

// UNSET
void		unset_variable(char **cmds, t_envp *envp_d);

//SIGNALS
void		signal_handler(void);

#endif