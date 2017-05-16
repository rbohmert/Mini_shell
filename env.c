/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 22:02:48 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/10 20:24:06 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cp_env(char **env)
{
	int		i;
	char	**nenv;

	i = 0;
	while (env[i])
		i++;
	nenv = (char **)malloc((i + 10) * sizeof(char *));
	i = 0;
	while (env[i])
	{
		nenv[i] = env[i];
		i++;
	}
	nenv[i] = NULL;
	return (nenv);
}

void	clr_env(char **nenv)
{
	int i;

	i = -1;
	while (nenv[++i])
	{
		free(nenv[i]);
		nenv[i] = NULL;
	}
}

void	add_key(char *str, char ***nenv)
{
	int		i;
	char	**new;

	i = 0;
	while ((*nenv)[i])
		i++;
	if (!(new = malloc((i + 2) * sizeof(char *))))
		return ;
	i = -1;
	while ((*nenv)[++i])
		new[i] = ft_strdup((*nenv)[i]);
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	ft_tabfree(nenv);
	*nenv = new;
}

char	**env_opt(char **arg, char **env, int *i)
{
	char	**nenv;

	nenv = malloc_env(env);
	while (arg[*i] && arg[*i][0] == '-')
	{
		if (arg[*i][1] == 'i' && arg[*i][2] == 0)
			clr_env(nenv);
		else if (arg[*i][1] == 'u' && arg[*i][2] == 0 && arg[*i + 1])
			ft_unsetenv(arg + (*i)++, nenv);
		else
		{
			ft_putstr_fd("usage env [-i] [-u name] [key=[arguments ...]]\n", 2);
			return (NULL);
		}
		(*i)++;
	}
	while (arg[*i] && ft_strchr(arg[*i], '='))
		add_key(arg[(*i)++], &nenv);
	return (nenv);
}

void	ft_env(char **arg, char **env)
{
	int		i;
	char	**nenv;
	char	*com;

	i = 1;
	if (!(nenv = env_opt(arg, env, &i)))
		return ;
	if (arg[i] && (com = check(env, arg[i], 1)))
		exe_com(com, arg + i, &nenv);
	else if (!arg[1])
		ft_ptabstr(nenv);
	else
	{
		ft_putstr("env: ");
		ft_putstr(arg[i]);
		ft_putstr(": commande introuvable\n");
	}
	ft_tabfree(&nenv);
}
