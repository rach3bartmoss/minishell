/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:48:16 by dopereir          #+#    #+#             */
/*   Updated: 2025/03/21 23:02:12 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command_pwd(t_data *shell)
{
	int	i;
	char	*buf;

	i = 0;
	buf = NULL;
	if (ft_strncmp(shell->tokens[i], "pwd", 3) == 0)
	{
		buf = getcwd(NULL, 0);
		printf("%s\n", buf);
		free(buf);
		buf = NULL;
	}
}