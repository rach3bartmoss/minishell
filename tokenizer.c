/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:28:33 by dopereir          #+#    #+#             */
/*   Updated: 2025/03/21 22:25:57 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_token(t_data *shell)
{
	int	i;

	i = 0;
	if (shell->tokens)
	{
		while (i < shell->token_count)
		{
			free(shell->tokens[i]);
			i++;
		}
		free (shell->tokens);
		shell->tokens = NULL;
	}
	shell->token_count = 0;
}

int	token_counter(char *str, char delim)
{
	int	token_count_res;
	int	i;

	token_count_res = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == delim)
			i++;
		if (str[i] == '\0')
			break ;
		token_count_res++;
		while (str[i] && str[i] != delim)
			i++;
	}
	return (token_count_res);
}

char	**split_tokens(char *str, char delim, t_data *shell)
{
	char	*s;
	char	*start;
	char	**tokens;
	int		len;
	int		i;

	s = str;
	tokens = malloc((shell->token_count + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == delim)
			s++;
		if (*s == '\0')
			break ;
		start = s;
		while (*s && *s != delim)
			s++;
		len = s - start;
		tokens[i] = malloc(len + 1);
		if (!tokens[i])
		{
			for (int j = 0; j < i; j++)
				free(tokens[j]);
			free(tokens);
			return (NULL);
		}
		//ft_strlcpy(tokens[i], start, len);
		strncpy(tokens[i], start, len);
		tokens[i][len] = '\0';
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

void	tokenize_input(t_data *shell, char delim)
{
	//add clear_data
	clear_token(shell);
	shell->token_count = token_counter(shell->input, delim);
	shell->tokens = split_tokens(shell->input, delim, shell);
}

void	print_tokens(t_data *shell)
{
	for (int i = 0; i < shell->token_count; i++)
	{
		printf("TOKEN: <%s>\n", shell->tokens[i]);
	}
}
