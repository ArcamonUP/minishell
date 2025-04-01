/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lstfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:21:47 by achu              #+#    #+#             */
/*   Updated: 2025/03/29 20:40:38 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstfd	*ft_lstfd_new(int fd)
{
	t_lstfd	*new;

	new = (t_lstfd *)malloc(sizeof(t_lstfd));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void	ft_lstfd_add_back(t_lstfd **list, t_lstfd *new)
{
	t_lstfd	*temp;

	if (!new || !list)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_lstfd_clear(t_lstfd **list)
{
	t_lstfd	*temp;

	temp = *list;
	if (!list)
		return ;
	while (*list && list)
	{
		temp = (*list)->next;
		*list = temp;
		free(list);
	}
}
