/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:48:16 by dopereir          #+#    #+#             */
/*   Updated: 2025/06/03 23:17:33 by dopereir         ###   ########.fr       */
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
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	execute(t_lexer *lexer)
{
	char	*command;
	char	*dir;
	char	full_path[1024];
	int		i;
	int		j;

	command = ft_strdup(lexer->tokens[0].text);//COMMAND ex: LS, ECHO, TOUCH, etc.

	i = 1;
	j = 0;
	while (i < lexer->token_count && argv_delimiter(lexer->tokens[i].text) == 0) //will create the arguments of the current command
	{
		lexer->args[j] = ft_strdup(lexer->tokens[i].text);
		i++;
		j++;
	}
	lexer->args[j] = NULL;
	
	lexer->path = getenv("PATH");
	dir = strtok(lexer->path, ":");
	while (dir)
	{
		ft_strcpy(full_path, dir);
		ft_strcat(full_path, "/");
		ft_strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, lexer->args, NULL);
		}
		dir = ft_strtok(NULL, ":");
	}
	free(command);
	for (i = 0; lexer->args[i] != NULL; i++)
		free(lexer->args[i]);
}
