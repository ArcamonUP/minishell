/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 23:20:20 by achu              #+#    #+#             */
/*   Updated: 2025/03/31 02:09:13 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
//#include "libft.h"
#include <stdio.h>
#include <dirent.h>

static int	get_patern(char *find)
{
	int	id;
	int	i;

	i = 0;
	id = 0;
	while (find[i])
	{
		if (find[i] == '*')
		{
			if (!find[i - 1])
				id += 1;
			else if (!find[i + 1])
				id += 2;
			else
				id += 4;
		}
		i++;
	}
	return (id);
}

static int	proccess_wild(char *str, char *find, int id)
{
	int	rem;
	int	result;

	rem = id;
	result = id;
	if (rem >= 4)
	{
		
		rem -= 4;
	}
	else if (rem >= 2)
	{
		rem -= 2;
	}
	else if (rem >= 1)
	{
		
		rem -= 1;
	}
	if (rem != 0)
		return (0);
	return (1);
}

char	**all_wild(char *find, int id)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (perror("Cannot open .\n"), 1);
	entry = readdir(dir);
	while (entry)
	{
		proccess_wild(entry->d_name, find, id);
		entry = readdir(dir);
	}
	closedir(dir);
}

int main(int argc, char **argv)
{
	char	**wildcard;
	int		id;

	id = get_patern(argv[1]);
	if (id > 0)
		{
			wildcard = all_wild(argv[1], id);
			if (!wildcard)
				return (1);
		}
	return (0);
}
