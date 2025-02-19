/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lstfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achu <achu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 02:21:47 by achu              #+#    #+#             */
/*   Updated: 2025/02/19 02:39:14 by achu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lstfd	*ft_lstfd_new(int fd)
{
	t_lstfd	*result;

	result = (t_lstfd *)malloc(sizeof(*result));
	if (!result)
		return (NULL);
	result->fd = fd;
	result->next = NULL;
	return (result);
}

void	ft_lstfd_add_back(t_lstfd **lst, t_lstfd *new)
{
	t_lstfd	*temp;

	temp = *lst;
	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_lstfd_clear(t_lstfd **lst)
{
	t_lstfd	*temp;

	temp = *lst;
	if (!lst)
		return ;
	while (*lst && lst)
	{
		temp = (*lst)->next;
		free(lst);
		*lst = temp;
	}
}
