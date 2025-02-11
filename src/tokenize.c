/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:41:17 by achu              #+#    #+#             */
/*   Updated: 2025/02/11 15:03:28 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		is_space(char c);
int		is_operator(char c);
int		ft_token_count(const char *line);
void	clear_double(char **ptr);

static char	*ft_token_op(const char *line)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (line[len] && is_operator(line[len]))
		len++;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static char	*ft_token_cmd(const char *line)
{
	int		i;
	int		len;
	char	*str;
	char	*trim;

	i = 0;
	len = 0;
	while (line[len] && !is_operator(line[len]))
		len++;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < len)
	{
		str[i] = line[i];
		i++;
	}
	str[i] = 0;
	trim = ft_strtrim(str, " ");
	free(str);
	if (!trim)
		return (NULL);
	return (trim);
}

char	**ft_tokenize(const char *line)
{
	int		count;
	char	**shell;

	count = 0;
	shell = (char **)ft_calloc(ft_token_count(line) + 1, sizeof(char *));
	if (!shell)
		return (NULL);
	while (*line)
	{
		if (*line && is_operator(*line))
		{
			shell[count] = ft_token_op(line);
			if (!shell[count])
				return (clear_double(shell), NULL);
			count++;
			while (*line && is_operator(*line))
				line++;
		}
		else if (*line && !is_operator(*line))
		{
			shell[count] = ft_token_cmd(line);
			if (!shell[count])
				return (clear_double(shell), NULL);
			count++;
			while (*line && !is_operator(*line))
				line++;
		}
		while (*line && is_space(*line))
			line++;
	}
	shell[count] = 0;
	return (shell);
}
