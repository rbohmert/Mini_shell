/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 20:34:18 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/15 21:22:47 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		new_len(char *str)
{
	int		len;
	int		i;
	char	*tmp;
	char	*var;

	len = 0;
	while (*str)
	{
		len = (*str == '"' && ft_strchr(str + 1, '"')) ? len - 2 : len;
		if (*str == '$')
		{
			i = 1;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var = ft_strndup(str + 1, i - 1);
			tmp = ft_strjoin(var, "=");
			free(var);
			len += (var = get_env(sg_env(NULL), tmp)) ? (int)ft_strlen(var) - i : -i;
			free(tmp);
		}
		str++;
		len++;
	}
	return (len);
}

void	expand_var(char **dst, char **src)
{
	char	*var;
	int		i;
	char	*tmp;

	i = 1;
	while ((*src)[i] && (ft_isalnum((*src)[i]) || (*src)[i] == '_'))
		i++;
	var = ft_strndup(*src + 1, i - 1);
	tmp = ft_strjoin(var, "=");
	free(var);
	if ((var = get_env(sg_env(NULL), tmp)))
	{
		ft_strcpy(*dst, var);
		*dst += ft_strlen(*dst);
	}
	free(tmp);
	*src += i;
}

void	cpy_arg(char *dst, char *src)
{
	char	*sav2ndcote;

	sav2ndcote = NULL;
	while (*src)
	{
		if (*src == '"' && (sav2ndcote == src ||\
			(sav2ndcote = ft_strchr(src + 1, '"'))))
		{
			src++;
			sav2ndcote = sav2ndcote == src ? NULL : sav2ndcote;
		}
		else if (*src == '$')
			expand_var(&dst, &src);
		else
			*(dst++) = *(src++);
	}
}

void	expand_tild(char **str)
{
	char *tmp;
	char *new;

	while ((tmp = ft_strchr(*str, '~')))
	{
		if (!(new = ft_strnew(ft_strlen(*str) + 5)))
			return ;
		ft_strncpy(new, *str, tmp - *str);
		ft_strcat(new, "$HOME");
		ft_strcat(new, tmp + 1);
		free(*str);
		*str = new;
	}
}

void	expend_arg(char **arg)
{
	int		i;
	char	*str;

	i = -1;
	while (arg[++i])
	{
		expand_tild(arg + i);
		str = ft_strnew(new_len(arg[i]) + 1);
		cpy_arg(str, arg[i]);
		free(arg[i]);
		arg[i] = str;
	}
}
