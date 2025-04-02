/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:46:05 by achu              #+#    #+#             */
/*   Updated: 2025/04/03 00:30:38 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	expand_token(char **tokens, int *idx, char *str)
{
	int	i;

	i = *idx;
	tokens = ft_realloc(tokens, i * sizeof(char *), (i + 2) * sizeof(char *));
	tokens[i] = strdup(str);
    tokens[i + 1] = NULL;
    *idx++;
}

static char	*do_squote(char **str)
{
	char	buffer[1024];
	size_t	i;

	i = 0;
	if (**str && **str == '\'')
		(*str)++;
	while (**str && **str != '\'')
	{
		buffer[i] = **str;
		(*str)++;
		i++;
	}
	buffer[i] == '\0';
	if (**str && **str == '\'')
		(*str)++;
	return (ft_strdup(buffer));
}

static char	*do_dquote(char **str, char **envp)
{
	char	buffer[1024];
	char	*var;
	size_t	i;

	i = 0;
	if (**str && **str == '"')
		(*str)++;
	while (**str && **str != '"')
	{
		if (**str && **str == '$')
		{
			var = do_var(*str, envp);
			ft_strjoin(&buffer[i], var);
			i += strlen(var);
		}
		buffer[i] = **str;
		(*str)++;
		i++;
	}
	buffer[i] == '\0';
	if (**str && **str == '"')
		(*str)++;
	return (ft_strdup(buffer));
}

static char	*do_var(char **str, char **envp)
{
	char	buffer[1024];
	size_t	i;

	i = 0;
	if (**str && **str == '$')
		(*str)++;
	while (**str && ft_isalnum(**str))
	{
		buffer[i] = **str;
		(*str)++;
		i++;
	}
	buffer[i] == '\0';
	return (get_var(buffer, envp));
}

static int	add_join(char **buffer, char *join, size_t *i, size_t *size)
{
	char	*new_buffer;
	size_t	new_size;
	size_t	len;	

	len = ft_strlen(join);
	if (*i + len + 1 >= *size)
	{
		new_size = (*i + len + 1) * 2;
		new_buffer = ft_realloc(*buffer, *size, new_size);
		if (!new_buffer)
			return (0);
		*buffer = new_buffer;
		*size = new_size;
	}
	ft_strcat(*buffer + *i, join);
	*i += len;
	free(join);
	return (1);
}

static int	add_char(char **buffer, char c, size_t *i, size_t *size)
{
	char	*new_buffer;
	size_t	new_size;

	if (*i + 1 >= *size)
	{
		new_size = *size * 2;
		new_buffer = ft_realloc(*buffer, *size, new_size);
		if (!new_buffer)
			return (0);
		*buffer = new_buffer;
		*size = new_size;
	}
	(*buffer)[(*i)++] = c;
	(*buffer)[*i] = '\0';
	return (1);
}

static char	*cal_customlen(char *str, char **envp)
{
	char	*buffer;
	size_t	size;
	size_t	i;

	i = 0;
	size = 1024;
	buffer = (char *)malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	while (*str)
	{
		if (*str && *str == '\'')
			add_join(&buffer, do_squote(&str), &i, &size);
		else if (*str && *str == '"')
			add_join(&buffer, do_dquote(&str, envp), &i, &size);
		else if (*str && *str == '$')
			add_join(&buffer, do_var(&str, envp), &i, &size);
		else
			add_char(&buffer, *str, &i, &size);
		str++;
	}
	return (buffer);
}

void	ft_custom_split(char *cmd)
{
	//ft_printf("len: %i\n", cal_customlen(cmd));
}