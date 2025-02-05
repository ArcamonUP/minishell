/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:48:44 by achu              #+#    #+#             */
/*   Updated: 2025/02/05 01:14:54 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_operator(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (1);
	else if (c == '|')
		return (1);
	else if (c == '&')
		return (1);
	return (0);
}

int	ft_countshell(const char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (is_operator(line[i]))
			count++;
		while (line[i] != '\0' && is_operator(line[i]))
			i++;
		if (line[i] != '\0')
			count++;
		while (line[i] != '\0' && !is_operator(line[i]))
			i++;
	}
	return (count);
}

int	ft_countcmd(const char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] || !is_operator(line[i]))
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i])
			count++;
		while (line[i] &&  line[i] != ' ')
			i++;
	}
	return (count);
}

void	clear_double(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	clear_triple(char ***ptr)
{
	int	i;
	int	j;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		j = 0;
		while (ptr[i][j])
		{
			free(ptr[i][j]);
			j++;
		}
		free(ptr[i]);
		i++;
	}
	free(ptr);
}