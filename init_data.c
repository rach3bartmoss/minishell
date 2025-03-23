/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:52:03 by dopereir          #+#    #+#             */
/*   Updated: 2025/03/23 17:21:45 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *shell)
{
	shell->input = NULL;
	shell->tokens = NULL;
	shell->token_count = 0;
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	shell->pid = 0;
}

/*
t_command	**parse_input(t_data *shell)
{
	int	i;
	t_command	**commands;

	commands = malloc((shell->token_count + 1) * sizeof(t_command *));
	if (!commands)
		return (NULL);
	i = 0;
	while (i < shell->token_count)
	{
		strcpy(shell->tokens[i], commands[i]);
		commands[i][strlen(shell->tokens[i] + 1)] = '\0';
		i++;
	}
}*/