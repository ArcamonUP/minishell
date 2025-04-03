/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:46:05 by achu              #+#    #+#             */
/*   Updated: 2025/04/03 01:52:14 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	req_realloc(char	**buffer, size_t *size, size_t need);

static char	*do_var(char **str, char **envp)
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
	if (**str && **str == '$')
		(*str)++;
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

static char	*do_dquote(char **str, char **envp)
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
	if (**str && **str == '"')
		(*str)++;
	while (**str && **str != '"')
	{
		if (**str && **str == '$')
		{
			var = do_var(str, envp);
			if (!req_realloc(&buffer, &size, i + ft_strlen(var) + 1))
				return (NULL);
			ft_strcat(&buffer[i], var);
			i += ft_strlen(var);
			free(var);
		}
		else
		{
			if (!req_realloc(&buffer, &size, i + 1))
				return (NULL);
			buffer[i] = **str;
			i++;		
		}
		(*str)++;
	}
	buffer[i] = '\0';
	if (**str && **str == '"')
		(*str)++;
	return (buffer);
}

static char	*do_squote(char **str)
{
	char	*buffer;
	size_t	size;
	size_t	i;

	i = 0;
	size = 1024;
	buffer = (char *)malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	if (**str && **str == '\'')
		(*str)++;
	while (**str && **str != '\'')
	{
		if (!req_realloc(&buffer, &size, i + 1))
			return (NULL);
		buffer[i] = **str;
		(*str)++;
		i++;
	}
	buffer[i] = '\0';
	if (**str && **str == '\'')
		(*str)++;
	return (buffer);
}

static int	add_join(char **buffer, char *join, size_t *i, size_t *size)
{
	size_t	len;	

	len = ft_strlen(join);
	if (!req_realloc(buffer, size, *i + len + 1))
			return (0);
	ft_strcat(*buffer + *i, join);
	*i += len;
	free(join);
	return (1);
}

static int	add_schar(char **buffer, char c, size_t *i, size_t *size)
{
	if (!req_realloc(buffer, size, *i + 1))
		return (0);
	(*buffer)[(*i)++] = c;
	(*buffer)[*i] = '\0';
	return (1);
}

static char	*craft_arg(char *str, char **envp)
{
	char	*buffer;
	size_t	size;
	size_t	i;

	i = 0;
	size = 1024;
	buffer = (char *)malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	while (*str && !ft_isspace(*str))
	{
		if (*str && *str == '\'')
			add_join(&buffer, do_squote(&str), &i, &size);
		else if (*str && *str == '"')
			add_join(&buffer, do_dquote(&str, envp), &i, &size);
		else if (*str && *str == '$')
			add_join(&buffer, do_var(&str, envp), &i, &size);
		else
		{
			add_schar(&buffer, *str, &i, &size);
			str++;
		}
	}
	return (buffer);
}

void	ft_custom_split(char *cmd, char **envp)
{
	ft_printf("test: %s\n", craft_arg(cmd, envp));
}