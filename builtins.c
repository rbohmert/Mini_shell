/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 22:39:24 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/18 19:09:45 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	addenv(char *key, char *value, char ***env)
{
	int		i;
	char	**nenv;

	i = 0;
	while ((*env)[i])
		i++;
	if (!(nenv = (char **)malloc((i + 2) * sizeof(char *))))
		return ;
	i = -1;
	while ((*env)[++i])
		nenv[i] = ft_strdup((*env)[i]);
	nenv[i] = ft_strjoin(key, value);
	nenv[i + 1] = NULL;
	ft_tabfree(env);
	*env = nenv;
	sg_env(*env);
}

void	ft_chdir(char *target, char ***env)
{
	char buf[200];
	char *arg[4];
	char oldpwd[200];

	arg[3] = NULL;
	ft_bzero(buf, 200);
	ft_bzero(oldpwd, 200);
	getcwd(oldpwd, 200);
	if (!chdir(target))
	{
		getcwd(buf, 200);
		if (get_env(*env, "OLDPWD="))
			change_env("OLDPWD=", *env, ft_strjoin("OLDPWD=", oldpwd));
		else
			addenv("OLDPWD=", oldpwd, env);
		if (get_env(*env, "PWD="))
			change_env("PWD=", *env, ft_strjoin("PWD=", buf));
		else
			addenv("PWD=", buf, env);
	}
	else
		ft_putstr_fd("File not exist or no access right\n", 2);
}

void	cd(char **arg, char ***env)
{
	int		i;
	char	pwd[200];

	i = 0;
	ft_bzero(pwd, 200);
	while (arg[i])
		i++;
	if (i > 2)
		ft_putstr_fd("Too many arguments\n", 2);
	else
	{
		if (arg[1] == NULL)
			get_env(*env, "HOME=") ? ft_chdir(get_env(*env, "HOME="), env) : 0;
		else if (arg[1][0] == '-')
			get_env(*env, "OLDPWD") ?\
			ft_chdir(get_env(*env, "OLDPWD="), env) : 0;
		else
			ft_chdir(arg[1], env);
	}
}

void	ft_unsetenv(char **arg, char **env)
{
	int ac;
	int i;

	ac = 0;
	i = -1;
	while (arg[ac])
		ac++;
	if (ac == 1)
		ft_ptabstr(env);
	if (ac == 2 || !ft_strcmp(arg[0], "-u"))
	{
		while (env[++i])
		{
			if (!ft_strncmp(env[i], arg[1], ft_strlen(arg[1])))
			{
				free(env[i]);
				env[i] = NULL;
				while (env[++i])
					env[i - 1] = env[i];
				env[i - 1] = NULL;
				break ;
			}
		}
	}
}

void	echo(char **arg)
{
	arg++;
	while (*arg)
	{
		ft_putstr(*arg);
		(*(arg + 1)) ? ft_putchar(' ') : ft_putchar('\n');
		arg++;
	}
}
