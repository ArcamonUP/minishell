/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbaridon <kbaridon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:19:51 by kbaridon          #+#    #+#             */
/*   Updated: 2025/02/24 11:12:25 by kbaridon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

int	get_fd_file(t_node node, char *str, int bonus)
{
	int	fd;

	fd = -1;
	while (node.right && ft_strncmp(node.str, str, 2) != 0)
		node = *(node.right);
	if (ft_strncmp(node.str, str, 2) == 0 && node.right)
	{
		if (bonus)
			fd = open(node.right->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(node.right->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (error("Failed to open file.", NULL), -1);
	}
	else
		return (-1);
	return (fd);
}

char	*get_limiter(t_node node)
{
	char	*result;

	result = NULL;
	while (node.right && ft_strncmp(node.str, ">>\0", 3) != 0)
		node = *(node.right);
	if (ft_strncmp(node.str, ">>\0", 3) == 0 && node.right)
	{
		result = ft_strdup(node.right->str);
		if (!result)
			return (error("Malloc failed.", NULL), NULL);
	}
	return (result);
}

t_pipex_data	init_pipex(t_node node, char **envp)
{
	t_pipex_data	data;
	char			**temp;

	data.cmd = NULL;
	temp = ft_calloc(sizeof(char *), 3);
	if (!temp)
		return (error("Malloc failed.", NULL), data);
	if (node.left->type == CMD)
		temp[0] = ft_strdup(node.left->str);
	else
		temp[0] = ft_strjoin("echo ", node.left->str); //Ici node.left->str doit etre remplace
		//par une fonction qui va chercher le contenu de la variable (un exec)
	if (!temp[0])
		return (error("Malloc failed.", NULL), free_tab(temp), data);
	if (node.right->type == CMD)
		temp[1] = ft_strdup(node.right->str);
	else
		temp[1] = ft_strjoin("echo ", node.right->str); //De meme ici
	if (!temp[1])
		return (error("Malloc failed.", NULL), free_tab(temp), data);
	data.cmd = temp;
	data.envp = envp;
	data.limiter = get_limiter(node);
	data.pid_tab = NULL;
	return (data);
}
