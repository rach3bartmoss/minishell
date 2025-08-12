/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:46:12 by nayara            #+#    #+#             */
/*   Updated: 2025/07/19 01:48:37 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft/libft.h"
#include "minishell.h"
#include <time.h>

//return a allocated memory block, assumes caller will free it
char	*get_special_var(char *var_name, t_lexer *lexer)
{
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(lexer->exit_status));
	else if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(getppid()));
	else if (ft_strcmp(var_name, "0") == 0)
		return (ft_strdup("minishell"));
	else if (ft_strcmp(var_name, "#") == 0)
		return (ft_strdup("0"));
	else if (ft_strcmp(var_name, "*") == 0)
		return (ft_strdup(""));
	else if (ft_strcmp(var_name, "@") == 0)
		return (ft_strdup(""));
	else if (ft_strcmp(var_name, "!") == 0)
	{
		if (lexer->last_bg_pid > 0)
			return (ft_itoa(lexer->last_bg_pid));
		else
			return (ft_strdup(""));
	}
	return (NULL);
}

int	set_value(char *var_value, char	*var_name, t_lexer *lexer, t_env *my_env)
{
	var_value = get_special_var((char *)var_name, lexer);
	if (!var_value)
		var_value = ft_getenv(my_env, var_name);
	if (!var_value)
		var_value = ft_strdup("");
	if (!var_value)
		return (-1);
	return (0);
}

//return 0 on sucess
//return -1 on failure
int	exp_var_iter(t_lexer *lexer, t_env *my_env, int i)
{
	int		is_alloc;
	char	*var_value;
	char	*old_text;

	is_alloc = 1;
	var_value = get_special_var(lexer->tokens[i].text + 1, lexer);
	if (!var_value)
	{
		var_value = ft_getenv(my_env, lexer->tokens[i].text + 1);
		is_alloc = 0;
	}
	if (!var_value)
	{
		var_value = ft_strdup("");
		is_alloc = 1;
	}
	if (!var_value)
		return (-1);
	old_text = lexer->tokens[i].text;
	lexer->tokens[i].text = ft_strdup(var_value);
	lexer->tokens[i].type = T_WORD;
	free(old_text);
	if (is_alloc)
		free(var_value);
	return (0);
}

int	expand_variables(t_lexer *lexer, t_env *my_env)
{
	int		i;
	int		rc;

	i = 0;
	while (i < lexer->token_count)
	{
		if (lexer->tokens[i].type == T_VAR)
		{
			rc = exp_var_iter(lexer, my_env, i);
			if (rc == -1)
				return (rc);
		}
		i++;
	}
	return (0);
}

char	*expand_heredoc_line(char *line, t_env *env)
{
	int		i;
	char	*out;
	char	*key;

	i = 0;
	out = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
		{
			key = hd_helper_extract_key(line, &i);
			if (key)
				out = hd_helper_exp_varname(out, key, env);
			else
				out = hd_helper_append_char(out, line[i++]);
		}
		else
			out = hd_helper_append_char(out, line[i++]);
	}
	return (out);
}

/* ORIGINAL FUNCTION THAT WORKS BEFORE REFACTORING
char	*expand_heredoc_line2(char *line, t_env *env)
{
	int		i;
	int		start;
	char	*key;
	char	*out;

	i = 0;
	out = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
		{
			start = i++;
			key = NULL;
			if (line[i] == '(')
			{
				i++; // skip '('
				size_t name_start = i;
        while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
					i++;
				if (line[i] == ')')
				{
					key = ft_substr(line, name_start, i - name_start);
					i++; // skip ')'
				}
				else
        i = start + 1;
			}
			else
			{
				size_t name_start = i;
				while (line[i] && (isalnum(line[i]) || line[i]=='_'))
					i++;
				key = ft_substr(line, name_start, i - name_start);
			}
			if (key)
			{
				char	*raw_value = ft_getenv(env, key);
				char	*val;

				if (raw_value)
					val = ft_strdup(raw_value);
				else
					val = ft_strdup("");
				out = ft_strjoin_free(out, val, 'L');//R
				free(val);
				free(key);
				continue ;
			}
			out = ft_strjoin_free(out, "$", 'L');//N
		}
		else
		{
			char tmp[2] = { line[i], '\0' };
			out = ft_strjoin_free(out, tmp, 'L');//R
			i++;
		}
	}
	return (out);
