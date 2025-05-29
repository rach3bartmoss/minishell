/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:08:53 by dopereir          #+#    #+#             */
/*   Updated: 2025/05/28 23:23:26 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"

typedef enum e_command_type
{
	CMD_SIMPLE,		// Single command like "ls", "echo", "pwd", "touch"
	CMD_SEQUENCE,	// Commands connected by &&, ||, ;
	CMD_PIPELINE	// Commands connected by |
}			t_command_type;

typedef struct s_simple_cmd
{
	char		**argv;
	//t_redirect	*redirects;		// Array of redirections
	int			redirect_count;
	bool		background;		// True if & was specified
}			t_simple_cmd;

typedef struct s_cmd_sequence
{
	struct s_command	**commands;	// Array of commands
	t_token_type		*operators;	// Array of &&, ||, ; between them
	int					count;
}			t_cmd_sequence;

typedef struct s_pipeline
{
	struct s_command	**commands;	// Array of simple commands
	int					count;
}			t_pipeline;

typedef struct s_command
{
	t_command_type	type;
	union {
		t_simple_cmd	simple;
		t_cmd_sequence	sequence;
		t_pipeline		pipeline;
	} data;
}			t_command;

#endif