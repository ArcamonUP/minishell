/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argsplit_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:51:14 by achu              #+#    #+#             */
/*   Updated: 2025/04/08 11:40:15 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		req_realloc(char **buffer, size_t *size, size_t need);
int		add_schar(char **buffer, char **str, size_t *size, size_t *i);
int		add_var(char **buffer, char *var, size_t *size, size_t *i);

static void	req_step(char **str, char find)
{
	if (**str && **str == find)
		(*str)++;
}

char	*do_var(char **str, char **envp)
{
	char	*buffer;
	char	*var;
	size_t	size;
	size_t	i;

	i = 0;
	size = 1024;
	buffer = (char *)malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	req_step(str, '$');
	while (**str && ft_isalnum(**str))
	{
		if (!req_realloc(&buffer, &size, i + 1))
			return (NULL);
		buffer[i] = **str;
		(*str)++;
		i++;
	}
	buffer[i] = '\0';
	var = get_var(buffer, envp);
	if (!var)
		return (free(buffer), ft_strdup(""));
	return (free(buffer), var);
}

char	*do_squote(char **str)
{
	char	*buffer;
	size_t	size;
	size_t	i;

	i = 0;
	size = 1024;
	buffer = (char *)malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	req_step(str, '\'');
	while (**str && **str != '\'')
	{
		if (!req_realloc(&buffer, &size, i + 1))
			return (NULL);
		buffer[i] = **str;
		(*str)++;
		i++;
	}
	buffer[i] = '\0';
	req_step(str, '\'');
	return (buffer);
}

char	*do_dquote(char **str, char **envp)
{
	char	*buffer;
	char	*var;
	size_t	size;
	size_t	i;

	i = 0;
	size = 1024;
	buffer = (char *)malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	req_step(str, '"');
	while (**str && **str != '"')
	{
		if (**str && **str == '$')
		{
			var = do_var(str, envp);
			if (!add_var(&buffer, var, &size, &i))
				return (free(buffer), free(var), NULL);
		}
		else if (!add_schar(&buffer, str, &size, &i))
			return (free(buffer), NULL);
	}
	buffer[i] = '\0';
	req_step(str, '"');
	return (buffer);
}
