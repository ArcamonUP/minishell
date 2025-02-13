/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:16:37 by achu              #+#    #+#             */
/*   Updated: 2025/02/13 17:44:59 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>

int	ft_exec_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (dup2(fd, INPUT) < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_exec_trunc(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT | 0644);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_exec_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT | 0644);
	if (fd < 0)
		return (1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	ft_exec_here_doc(char *file)
{
	//ouais faut faire le here doc ici quoi
	//le here_doc de base att que tout le commande
	//soit execute avamtde le lancer sur le terminal
	//cad que "cat << LIM && echo true && cat << TOTO"
	//le echo true doit etre ecrit entre LIM et TOTO
	return (0);
}