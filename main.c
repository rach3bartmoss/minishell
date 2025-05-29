/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:15:37 by dopereir          #+#    #+#             */
/*   Updated: 2025/05/29 20:37:56 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->input = NULL;
	lexer->tokens = NULL;
	lexer->token_count = 0;

	while(keepRunning)
	{
		lexer->input = readline("PROMPT>$ "); // READ (1/2)
		if (lexer->input)
		{
			lexing_input(lexer, ' '); // READ(2/2)
			print_tokens(lexer); // PRINT TOKENS
			free (lexer->input);
		}
		keepRunning = 0;
	}
	return (0);
}
