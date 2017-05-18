/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_2front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 19:02:07 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/18 19:02:08 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_push_2front(t_2list **lst, void *content)
{
	t_2list *tmp;

	tmp = *lst;
	if (tmp)
	{
		tmp = ft_create_2lst(content);
		tmp->next = *lst;
		(*lst)->prev = tmp;
		*lst = tmp;
	}
	else
		*lst = ft_create_2lst(content);
}
