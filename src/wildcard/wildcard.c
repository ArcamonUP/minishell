/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:20:20 by achu              #+#    #+#             */
/*   Updated: 2025/04/04 13:58:00 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	**get_tokens(char *find);
int		is_wildcard(char *str, char **tokens);

static void	rev_astrisk(char *str)
{
	while (*str)
	{
		if ((unsigned char)*str == 0xFF)
			*str = '*';
		str++;
	}
}

static int	cal_len(char **tokens)
{
	int				i;
	DIR				*dir;
	struct dirent	*entry;

	i = 0;
	dir = opendir(".");
	if (!dir)
		return (ft_perror("Cannot open . dir\n"), 0);
	entry = readdir(dir);
	while (entry)
	{
		if (!(entry->d_name[0] == '.' && ft_strncmp(tokens[0], ".", 1) != 0) && \
			is_wildcard(entry->d_name, tokens))
			i++;
		entry = readdir(dir);
	}
	closedir(dir);
	if (i == 0)
		return (1);
	return (i);
}

static char	**get_wilds(DIR *dir, char **tokens)
{
	int				i;
	char			**wilds;
	struct dirent	*entry;

	i = 0;
	wilds = ft_calloc(cal_len(tokens) + 1, sizeof(char *));
	if (!wilds)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (!(entry->d_name[0] == '.' && ft_strncmp(tokens[0], ".", 1) != 0) && \
			is_wildcard(entry->d_name, tokens))
		{
			wilds[i] = ft_strdup(entry->d_name);
			if (!wilds[i])
				return (clear_double(wilds), NULL);
			i++;
		}
		entry = readdir(dir);
	}
	wilds[i] = NULL;
	return (wilds);
}

char	**get_file(char *find)
{
	char	**tokens;
	char	**wilds;
	char	*temp;
	DIR		*dir;

	tokens = get_tokens(find);
	if (!tokens)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (ft_perror("Cannot open . dir\n"), NULL);
	wilds = get_wilds(dir, tokens);
	if (!wilds)
		return (NULL);
	if (!*wilds)
	{
		temp = ft_strdup(find);
		rev_astrisk(temp);
		wilds[0] = temp;
		wilds[1] = NULL;
	}
	clear_double(tokens);
	closedir(dir);
	return (wilds);
}
