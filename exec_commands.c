/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:48:16 by dopereir          #+#    #+#             */
/*   Updated: 2025/06/04 22:53:45 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	argv_delimiter(char *arg)
{
	char	*target_tokens[6];
	int		i;

	target_tokens[0] = "&&";
	target_tokens[1] = ">";
	target_tokens[2] = "<<";
	target_tokens[3] = ">>";
	target_tokens[4] = "|";
	target_tokens[5] = NULL;
	i = 0;
	while (target_tokens[i] != NULL)
	{
		if (ft_strcmp(arg, target_tokens[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	execute(t_lexer *lexer)
{
	char	full_path[1024];
	int		i;
	int		j;
	int		found_path_flag = 0;
	pid_t	pid;

	//adapt to use curr_cmd, we shall receive the t_parse_data structure and execute one by one

	i = 0;
	j = 0;
	while (i < lexer->token_count && argv_delimiter(lexer->tokens[i].text) == 0) //will create the arguments of the current command
	{
		lexer->args[j] = ft_strdup(lexer->tokens[i].text);
		i++;
		j++;
	}
	lexer->args[j] = NULL;
	found_path_flag = cmd_path_generator(lexer , full_path);
	if (found_path_flag)
	{
		pid = fork();
		if (pid == 0) //child process to execute
		{
			execve(full_path, lexer->args, NULL);
		}
		else if (pid > 0)
			wait(NULL);
		else
		{
			perror("fork in exec_commands.c failed");
		}
	}
	for (i = 0; lexer->args[i] != NULL; i++)
		free(lexer->args[i]);
}

void	exec_parsed_cmds(t_parse_data *cmd_list)
{

}
