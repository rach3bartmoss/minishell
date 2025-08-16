/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dopereir <dopereir@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 22:22:43 by dopereir          #+#    #+#             */
/*   Updated: 2025/08/12 22:23:27 by dopereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include <time.h>

int  append_char(char **dst, char c)
{
	char buf[2];
	char *tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = join_words(*dst, buf);
	if (!tmp)
		return (-1);
	*dst = tmp;
	return (0);
}


/*char	*expand_word_text(const char *src, int quot, t_env *env, int last_status)
{
	size_t	i = 0;
	size_t	j;
	char	*out = ft_strdup("");
	char	*tmp;
	char	*num;
	char	*name;
	char	*val;

	if (!out)
		return (NULL);
	while (src[i])
	{
		// Escaped dollar: \$VAR → literal $VAR
		if (src[i] == '\\')
		{
			if (quot == 2)
			{
				char next = src[i + 1];
				if (next == '$' || next == '`' || next == '"' || next == '\\')
				{
					if (append_char(&out, next) < 0)
					{
						free(out);
						return (NULL);
					}
					i += 2;
					continue;
				}
				if (append_char(&out, '\\') < 0)
				{
					free(out);
					return (NULL);
				}
				i++;
				continue;
			}
			else
			{
				// Unquoted: a backslash quotes the next char (except end of string)
				if (src[i + 1] != '\0')
				{
					if (append_char(&out, src[i + 1]) < 0)
					{
						free(out);
						return (NULL);
					}
					i += 2;
					continue;
				}
				// Trailing backslash: drop it
				i++;
				continue;
			}
		}
		if (src[i] == '$')
		{
			// Special: $?
			if (src[i + 1] == '?')
			{
				num = ft_itoa(last_status);
				if (!num)
				{
					free(out);
					return (NULL);
				}
				tmp = join_words(out, num);
				free (num);
				if (!tmp)
				{
					free(out);
					return (NULL);
				}
				free(out);
				out = tmp;
				tmp = NULL;
				i += 2;
				continue;
			}
			// Normal var: must start alpha/_
			j = i + 1;
			if (!(ft_isalpha(src[j]) || src[j] == '_'))
			{
				if (append_char(&out, '$') < 0)
				{
					free(out);
					return (NULL);
				}
				i++;
				continue;
			}
			while (ft_isalnum(src[j]) || src[j] == '_')
				j++;
			name = ft_substr(src, i + 1, j - (i + 1));
			if (!name)
			{
				free(out);
				return (NULL);
			}
			val = ft_getenv(env, name);
			tmp = join_words(out, val ? val : "");
			free(name);
			name = NULL;
			if (!tmp)
			{
				free(out);
				return (NULL);
			}
			free(out);
			out = tmp;
			tmp = NULL;
			i = j;
			continue;
		}
		if (append_char(&out, src[i]) < 0)
		{
			free(out);
			return (NULL);
		}
		i++;
	}
	return (out);
}*/

char	*expand_word_text(const char *src, int quot, t_env *env, int last_status)
{
	size_t	i = 0;
	size_t	j;
	char	*out = ft_strdup("");
	char	*tmp;
	char	*num;
	char	*name;
	char	*val;

	if (!out)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '\\')
		{
			if (quot == 2)
			{
				char next = src[i + 1];
				if (next == '$' || next == '`' || next == '"' || next == '\\')
				{
					if (append_char(&out, next) < 0)
						return (free(out), NULL);
					i += 2;
					continue;
				}
				if (append_char(&out, '\\') < 0)
					return (free(out), NULL);
				i++;
				continue;
			}
			else
			{
				if (src[i + 1] != '\0')
				{
					if (append_char(&out, src[i + 1]) < 0)
						return (free(out), NULL);
					i += 2;
					continue;
				}
				i++;
				continue;
			}
		}
		if (src[i] == '$')
		{
			if (src[i + 1] == '?')
			{
				printf("LAST STATUS-> <%d>\n", last_status);
				num = ft_itoa(last_status);
				printf("NUM-> <%s>\n", num);
				if (num)
				{
					printf("GOT HERE 1!\n");
					tmp = join_words(out, num);
				}
				else
				{
					printf("GOT HERE 2!\n");
					tmp = join_words(out, "");
				}
				printf("TMP-> <%s>\n", tmp);
				//free(out);
				out = ft_strdup(tmp);
				free (tmp);
				if (num)
					free(num);
				if (!out)
					return (NULL);
				return (out);
				i += 2;
				continue;
			}
			j = i + 1;
			if (!(ft_isalpha(src[j]) || src[j] == '_'))
			{
				if (append_char(&out, '$') < 0)
					return (free(out), NULL);
				i++;
				continue;
			}
			while (ft_isalnum(src[j]) || src[j] == '_')
				j++;
			name = ft_substr(src, i + 1, j - (i + 1));
			val = name ? ft_getenv(env, name) : NULL;
			tmp = join_words(out, val ? val : "");
			out = tmp;
			free(name);
			if (!out)
				return (NULL);
			i = j;
			continue;
		}
		if (append_char(&out, src[i]) < 0)
			return (free(out), NULL);
		i++;
	}
	return (out);
}
