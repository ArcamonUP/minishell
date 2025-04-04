/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argsplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:46:05 by achu              #+#    #+#             */
/*   Updated: 2025/04/04 16:32:05 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		expand_realloc(char	***buffer, size_t size);
int		add_join(char **buffer, char *join, size_t *i, size_t *size);
int		add_schar(char **buffer, char **str, size_t *size, size_t *i);
char	*do_var(char **str, char **envp);
char	*do_dquote(char **str, char **envp);
char	*do_squote(char **str);

static int	add_wild(char ***split, size_t *size, char *find)
{
	char	**files;
	size_t	i;

	i = 0;
	files = get_file(find);
	if (!files)
		return (0);
	while (files[i])
	{
		if (!expand_realloc(split, *size))
			return (clear_double(*split), 0);
		(*split)[*size] = files[i];
		(*size)++;
		i++;
	}
	return (1);
}

static int	add_argsplit(char ***split, size_t *size, char *new)
{
	if (!expand_realloc(split, *size))
		return (clear_double(*split), 0);
	(*split)[*size] = new;
	(*size)++;
	return (1);
}

static char	*get_arg(char **str, char **envp)
{
	char	*buffer;
	size_t	size;
	size_t	i;

	i = 0;
	size = 1024;
	buffer = (char *)malloc(size * sizeof(char));
	if (!buffer)
		return (NULL);
	while (**str && !ft_isspace(**str))
	{
		if (**str && **str == '\'')
			add_join(&buffer, do_squote(str), &size, &i);
		else if (**str && **str == '"')
			add_join(&buffer, do_dquote(str, envp), &size, &i);
		else if (**str && **str == '$')
			add_join(&buffer, do_var(str, envp), &size, &i);
		else
			add_schar(&buffer, str, &size, &i);
	}
	return (buffer);
}

static char	**get_argsplit(char *str, char **envp)
{
	char	**split;
	char	*temp;
	size_t	size;

	size = 0;
	split = (char **)malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	while (*str)
	{
		while (*str && ft_isspace(*str))
			str++;
		if (*str && !ft_isspace(*str))
		{
			temp = get_arg(&str, envp);
			if (!temp)
				return (clear_double(split), NULL);
			if (ft_strchr(temp, (unsigned char)0xFF))
				add_wild(&split, &size, temp);
			else
				add_argsplit(&split, &size, temp);
		}
	}
	split[size] = 0;
	return (split);
}

char	**ft_argsplit(char *str, char **envp)
{
	char	**args;
	int		in_squote;
	int		in_dquote;
	size_t	i;	

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
			in_squote = !in_squote;
		else if (str[i] && str[i] == '"')
			in_dquote = !in_dquote;
		else if (str[i] == '*' && !in_squote && !in_dquote)
			str[i] = (unsigned char)0xFF;
		i++;
	}
	args = get_argsplit(str, envp);
	if (!args)
		return (NULL);
	return (args);
}
