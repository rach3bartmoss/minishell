/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:10:10 by dopereir          #+#    #+#             */
/*   Updated: 2025/05/28 05:49:19 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "libft/libft.h"

typedef enum e_token_type
{
	T_WORD,			// simple word
	T_PIPE,			// | 
	T_REDIR_IN,		// <
	T_REDIR_OUT,	// >
	T_REDIR_APPEND,	// >>
	T_BACKGROUND,	// & execute command in background mode
	T_AND,			// &&
	T_WILDCARD,		// *.c for wildcards
	T_EOL			// END OF LINE
}			t_token_type;

//WHEN PARSING THE DELIMITER SHOULD ALSO BE SPECIFIQ CONTROLS LIKE
// redirections, pipes among other things
//ex:	 mkdir test&&cd test&&touch test.txt&&touch another.txt&&ls > test1.txt #THIS WORKS

typedef enum e_command_type
{
	CMD_SIMPLE,		// Single command like "ls", "echo", "pwd", "touch"
	CMD_SEQUENCE,	// Commands connected by &&, ||, ;
	CMD_PIPELINE	// Commands connected by |
}			t_command_type;

/*typedef struct s_simple_cmd
{
    char        **argv;          // Command and arguments
    t_redirect  *redirects;      // Array of redirections
    int          redirect_count;
    bool         background;     // True if & was specified
} t_simple_cmd;

typedef struct s_cmd_sequence
{
    struct s_command  **commands;    // Array of commands
    t_token_type      *operators;    // Array of &&, ||, ; between them
    int                count;
} t_cmd_sequence;

typedef struct s_pipeline
{
    struct s_command  **commands;    // Array of simple commands
    int                count;
} t_pipeline;*/

typedef struct s_command
{
	t_command_type	type;
	union {
		t_simple_cmd	simple;
		t_cmd_sequence	sequence;
		t_pipeline		pipeline;
	} data;
}			t_command;

typedef struct s_token
{
	t_token_type	type;
	char			*text;
}			t_token;

typedef struct s_tokenphase_data //lexical-analysis phase
{
	char	*input;
	t_token	*tokens;
	int		token_count;
}			t_token_data;

typedef struct s_parsephase_data
{
	t_command	*root_command;
}			t_parse_data;

static volatile	int	keepRunning = 1;



//main.c
void	sig_int_handler(int something);
//init_data.c
void	init_data(t_data *shell);
//tokenizer.c
void	print_tokens(t_data *shell); //TEMP FUNCTION FOR TESTING
void	clear_token(t_data *shell);
int		token_counter(char *str, char delim);
char	**split_tokens(char *str, char delim, t_data *shell);
void	tokenize_input(t_data *shell, char delim);
//exec_commands.c
void	execute_command_pwd(t_data *shell);
void	execute_command_exit(t_data *shell);

#endif
