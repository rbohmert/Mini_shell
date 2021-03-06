/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:57:16 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/18 18:57:34 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*new;
	int		i;

	i = -1;
	if (!(new = (char *)malloc(n + 1)))
		return (NULL);
	while (++i < n)
		new[i] = str[i];
	new[i] = 0;
	return (new);
}
