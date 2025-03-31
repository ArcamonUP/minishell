/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 02:00:52 by achu              #+#    #+#             */
/*   Updated: 2025/03/31 02:51:37 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// If the wildcard asterisk is at the end
int ft_end(char *str, char *find)
{
	char	buffer[1024];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (find[i] == '*')
	{
		buffer[i] = find[i];
		buffer[i + 1] = '\0';
		i++;
	}
    while (buffer[j])
	{
		if (str[j] != buffer[j])
			return (0);
		j++;
	}
	return (1);
}

int ft_middle(char *str, char *find)
{

}

// If the wildcard asterisk is at the beginning
int ft_start(char *str, char *find)
{
	char	buffer[1024];
	int		i;
	int		j;

	i = 0;
	while (find[i] == '*')
		i++;
	while (find[i] && find[i] != '*')
	{
		buffer[j] = find[i];
		buffer[j + 1] = '\0';
		i++;
		j++;
	}
	return (0);
}
