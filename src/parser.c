/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:41:17 by achu              #+#    #+#             */
/*   Updated: 2025/02/05 01:17:32 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		is_operator(char c);
int		ft_countshell(const char *line);
int		ft_countcmd(const char *line);
void	clear_double(char **ptr);
void	clear_triple(char ***ptr);

static char	*ft_opalloc(const char *line)
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

static char	**ft_split_operator(const char *line)
{
	char	**op;

	op = (char **)ft_calloc(2, sizeof(char *));
	if (!op)
		return (NULL);
	op[0] = ft_opalloc(line);
	if (!op[0])
		return (clear_double(op), NULL);
	op[1] = 0;
	return (op);
}

static char	*ft_cmdalloc(const char *line)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	while (line[len] && line[len] != ' ' && !is_operator(line[len]))
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

static char	**ft_split_cmd(const char *line)
{
	int		count;
	char	**cmds;

	count = 0;
	cmds = (char **)ft_calloc(ft_countcmd(line) + 1, sizeof(char *));
	if (!cmds)
		return (NULL);
	while (*line && !is_operator(*line))
	{
		while (*line && *line == ' ' && !is_operator(*line))
			line++;
		if (*line && !is_operator(*line))
		{
			cmds[count] = ft_cmdalloc(line);
			if (!cmds[count])
				return (clear_double(cmds), NULL);
			count++;
		}
		while (*line && *line != ' ' && !is_operator(*line))
			line++;
	}
	cmds[count] = 0;
	return (cmds);
}

char	***ft_split_shell(const char *line)
{
	int		count;
	char	***shell;

	count = 0;
	shell = (char ***)ft_calloc(ft_countshell(line) + 1, sizeof(char **));
	if (!shell)
		return (NULL);
	while (*line)
	{
		if (is_operator(*line))
		{
			shell[count] = ft_split_operator(line);
			if (!shell[count])
				return (clear_triple(shell), NULL);
			count++;
		}
		while (*line && is_operator(*line))
			line++;
		if (*line)
		{
			shell[count] = ft_split_cmd(line);
			if (!shell[count])
				return (clear_triple(shell), NULL);
			count++;
		}
		while (*line && !is_operator(*line))
			line++;
	}
	shell[count] = 0;
	return (shell);
}
