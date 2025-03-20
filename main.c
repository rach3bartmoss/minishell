/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 00:40:30 by dopereir          #+#    #+#             */
/*   Updated: 2025/03/20 00:40:33 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
//use -lreadline at compilation

static volatile	int	keepRunning = 1;

void	sig_int_handler(int something)
{
	keepRunning = 0;
	exit(0);
}

/*
FT_STRTOK TO TOKENS
HISTORY MANAGEMENT
OPTIMIZATIONS
*/
int	main(int ac, char **av)
{
	char	*input = "\0";
	signal(SIGINT, sig_int_handler);

	while(keepRunning)
	{
		input = readline("PROMPT>$ ");
		if (input)
		{
			printf("Here is your input: <%s>\n", input);
			add_history(input);
			free (input);
		}
	}
	return (0);
}