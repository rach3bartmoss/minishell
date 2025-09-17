/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nayara <nayara@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 23:45:43 by dopereir          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/09 17:43:13 by nayara           ###   ########.fr       */
=======
/*   Updated: 2025/09/09 15:32:51 by dopereir         ###   ########.fr       */
>>>>>>> 5fe75188209e5c772b3fc472f083b677515b9b15
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_hd_expand_helper(t_lexer *lexer, t_command *cmd,
	char *token_text, t_pbuilder *pb)
{
	int	len;

	len = ft_strlen(token_text);
	if (lexer->tokens[pb->i].type == T_VAR)
	{
		cmd->hd_expand = set_and_get(1);
		cmd->hd_delim = ft_strdup(token_text);
	}
	else if (len >= 2
		&& ((token_text[0] == '"' && token_text[len - 1] == '"')
			|| (token_text[0] == '\'' && token_text[len - 1] == '\'')))
	{
		cmd->hd_expand = set_and_get(0);
		cmd->hd_delim = ft_strndup(token_text + 1, len - 2);
	}
	else
	{
		cmd->hd_expand = 1;
		cmd->hd_delim = ft_strdup(token_text);
	}
}

static int	redir_heredoc_helper(t_command *cmd, t_lexer *lexer, t_pbuilder *pb)
{
	char	*token_text;

	if (cmd->hd_delim)
		free(cmd->hd_delim);
	if (!lexer->tokens[pb->i].text)
	{
		free(pb->acc);
		free_command(cmd);
		return (-1);
	}
	token_text = lexer->tokens[pb->i].text;
	redir_hd_expand_helper(lexer, cmd, token_text, pb);
	if (!cmd->hd_delim)
	{
		free(pb->acc);
		free_command(cmd);
		return (-1);
	}
	cmd->type = T_REDIR_HEREDOC;
	pb->i++;
	return (1);
}

//return (-1) on failure
//return (1) to continue
int	redir_heredoc_module(t_command *cmd, t_lexer *lexer, t_pbuilder *pb)
{
	pb->i++;
	if (pb->i < lexer->token_count && (lexer->tokens[pb->i].type == T_WORD
			|| lexer->tokens[pb->i].type == T_VAR))
		return (redir_heredoc_helper(cmd, lexer, pb));
	printf("minishell: syntax error near unexpected token `newline01'\n");
	free(pb->acc);
	free_command(cmd);
	return (-1);
}

int	acc_module(t_command *cmd, t_pbuilder *pb)
{
	if (pb->acc)
	{
		if (cmd->name == NULL)
		{
			cmd->name = ft_strdup(pb->acc);
			if (!cmd->name)
			{
				free(pb->acc);
				free_command(cmd);
				return (-1);
			}
		}
		if (pb->arg_index < MAX_ARGS - 1)
			cmd->argv[pb->arg_index++] = pb->acc;
		else
			free(pb->acc);
		pb->acc = NULL;
	}
	return (1);
}

int	parse_section1(t_command *cmd, t_lexer *lexer, t_pbuilder *pb)
{
	int	res;

	if (is_wordish(&lexer->tokens[pb->i]))
	{
		res = is_wordish_module(cmd, lexer, pb);
		if (res == -1)
			return (-1);
		return (1);
	}
	else if (lexer->tokens[pb->i].type == T_REDIR_IN)
		return (redir_in_module(cmd, lexer, pb));
	else if (lexer->tokens[pb->i].type == T_REDIR_OUT
		|| lexer->tokens[pb->i].type == T_REDIR_APPEND)
		return (redir_out_module(cmd, lexer, pb));
	else if (lexer->tokens[pb->i].type == T_REDIR_HEREDOC)
		return (redir_heredoc_module(cmd, lexer, pb));
	else if (lexer->tokens[pb->i].type == T_AND)
		return (2);
	return (0);
}
