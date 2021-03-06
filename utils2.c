/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 22:15:19 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/18 19:11:02 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**sg_env(char **env)
{
	static char **sav_env = NULL;

	if (!env)
		return (sav_env);
	sav_env = env;
	return (NULL);
}

int		isimprchar(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (!((*str > 31 && *str < 127) || *str == '\t' || *str == '\v'))
			return (0);
		str++;
	}
	return (1);
}

char	**malloc_env(char **env)
{
	int		i;
	int		j;
	char	**nenv;

	i = 0;
	j = 0;
	nenv = NULL;
	while (env[i++])
		;
	if (!(nenv = (char **)malloc((i + 1) * sizeof(char *))))
		return (NULL);
	while (env[j])
	{
		nenv[j] = ft_strdup(env[j]);
		j++;
	}
	nenv[j] = NULL;
	return (nenv);
}

char	*get_env(char **env, char *key)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(key);
	while (env[++i])
	{
		if (ft_strncmp(env[i], key, len) == 0)
			return (env[i] + len);
	}
	return (NULL);
}

void	exec_builtins(char *name, char **arg, char ***env)
{
	if (!(ft_strcmp(name, "cd")))
		cd(arg, env);
	if (!(ft_strcmp(name, "echo")))
		echo(arg);
	if (!(ft_strcmp(name, "env")))
		ft_env(arg, *env);
	if (!(ft_strcmp(name, "setenv")))
		ft_setenv(arg, env);
	if (!(ft_strcmp(name, "unsetenv")))
		ft_unsetenv(arg, *env);
	if (!(ft_strcmp(name, "exit")))
	{
		free(name);
		ft_tabfree(&arg);
		ft_tabfree(env);
		exit(0);
	}
	free(name);
}
