/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:10:10 by dopereir          #+#    #+#             */
/*   Updated: 2025/03/21 23:41:43 by dopereir         ###   ########.fr       */
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

typedef struct s_data
{
	char	*input;
	char	**tokens;
	int		token_count;
	pid_t	pid;
	int		fd_in;
	int		fd_out;
}			t_data;

typedef struct s_command
{
	char	**cmd_tokens;
	int		cmd_token_count;
	int		fd_in;
	int		fd_out;
}			t_command;

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
