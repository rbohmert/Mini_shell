/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freestrtab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 19:02:30 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/18 19:02:39 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freestrtab(char **strtab)
{
	int i;

	if (strtab == NULL)
		return ;
	i = 0;
	while (strtab[i])
		free(strtab[i++]);
	free(strtab);
}
