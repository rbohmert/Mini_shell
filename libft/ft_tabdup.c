/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 18:58:36 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/18 18:59:01 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab)
{
	int		i;
	char	**ntab;

	i = -1;
	while (tab[++i])
		;
	if (!(ntab = malloc((i + 1) * sizeof(char *))))
		return (NULL);
	i = -1;
	while (tab[++i])
		ntab[i] = ft_strdup(tab[i]);
	ntab[i] = NULL;
	return (ntab);
}
