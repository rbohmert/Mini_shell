/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 19:09:49 by rbohmert          #+#    #+#             */
/*   Updated: 2017/05/15 21:24:57 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*chrbinpath(char **env, char *name)
{
	int			i;
	char		**dir;
	struct stat buf;
	char		*path;

	i = -1;
	dir = (get_env(env, "PATH=") ? ft_strsplit(get_env(env, "PATH="), ':')\
	: NULL);
	while (dir && dir[++i] && (path = join_path(dir[i], name)))
	{
		if (!access(path, F_OK))
		{
			lstat(path, &buf);
			(buf.st_mode & S_IXUSR) && !S_ISDIR(buf.st_mode) ?\
			ft_tabfree(&dir) : 0;
			if ((buf.st_mode & S_IXUSR) && !S_ISDIR(buf.st_mode))
				return (path);
		}
		free(path);
	}
	ft_tabfree(&dir);
	return (NULL);
}

char	*check(char **env, char *name, int no_built)
{
	struct stat buf;

	if (!no_built && check_builtins(name))
		return (ft_strdup(name));
	else if (name[0] == '.' || name[0] == '/')
	{
		if (!access(name, F_OK | X_OK))
		{
			lstat(name, &buf);
			if (!S_ISDIR(buf.st_mode))
				return (ft_strdup(name));
			else
				return (NULL);
		}
	}
	return (chrbinpath(env, name));
}

void	exe_com(char *name, char **arg, char ***env)
{
	pid_t pid;

	if (name[0] != '/' && name[0] != '.')
		exec_builtins(name, arg, env);
	else
	{
		pid = fork();
		if (pid < 0)
			ft_putstr("fork fail\n");
		else if (pid == 0)
		{
			execve(name, arg, *env);
			ft_putstr("exec fail\n");
		}
		else
			waitpid(pid, 0, 0);
		free(name);
		return ;
	}
}

void	verif_line(char *str, char ***env)
{
	char **ltab;

	ltab = NULL;
	if (str[0])
	{
		ltab = make_arg(str);
		expend_arg(ltab);
		if (!(str = check(*env, ltab[0], 0)))
			ft_putstr("Command not found\n");
		else
			exe_com(str, ltab, env);
	}
	ft_tabfree(&ltab);
}

int		main(int ac, char **av, char **env)
{
	char	*line;

	ac = (av - av) + ac;
	env = malloc_env(env);
	sg_env(env);
	ft_putstr("$>");
	while (get_next_line(0, &line) && line)
	{
		if (isimprchar(line))
		{
			strtrim_nocote(&line);
			verif_line(line, &env);
			line != NULL ? free(line) : 0;
		}
		else
			ft_putendl("Invalid character");
		ft_putstr("$>");
	}
	return (0);
}
