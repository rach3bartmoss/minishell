/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:08:53 by dopereir          #+#    #+#             */
/*   Updated: 2025/06/28 17:26:58 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# define MAX_ARGS 1024

typedef struct s_command
{
	t_token_type		type; // Type of command
	char				*name; // Name of the command (e.g., "ls", "echo")
	char				*path; // generate path w/ cmd_path_generator()
	char				*input_file; // Input file for redirection
	char				*output_file; // Output file for redirection
	char				*argv[MAX_ARGS]; // Arguments for the command
	char				*filename; //path to file redirection
	char				*hd_delim; //delimiter to use on heredoc
	int					heredoc_fd;
	pid_t				pid_filename_output;
	// para pipelines e sequencias parser phase
	struct s_command	**commands; // arrray de comandos filhos
	int					command_count;
	struct s_command	*left;
	struct s_command	*right;
	int					next_is_pipe;
	int					next_is_and;
}			t_command;

#endif
