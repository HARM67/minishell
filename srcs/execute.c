/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:44:43 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/17 18:07:18 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_cmd2(t_app *app, char *path)
{
	DIR		*dirp;
	struct dirent	*d;
	t_stat			m_stat;
	char			*tmp;

	dirp = opendir(path);
	while ((d = readdir(dirp)))
		if (ft_strcmp(d->d_name, app->lst_cmd.first->command) == 0)
		{
			ft_sprintf(&tmp, "%s/%s", path, app->lst_cmd.first->command);
			stat(tmp, &m_stat);
			if (m_stat.st_mode & 0111)
				return (tmp);
		}
	return (0);
}

void	clean_tab(char **tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		free(tab[i]);
	free(tab);
}

char	*search_cmd(t_app *app)
{
	int				i;
	int				size;
	t_elem_env		*cmd;
	char			**tab;
	char			*rt;

	i = -1;
	cmd = get_env(app, "PATH");
	if (!cmd)
		put_error("Pas de path");
	size = ft_strcount(cmd->content, ':');
	tab = ft_strsplit(cmd->content, ':');
	while (++i < size)
	{
		if ((rt = search_cmd2(app, tab[i])))
		{
			clean_tab(tab, size);
			return (rt);
		}
	}
	clean_tab(tab, size);
	return (0);
}

void	execute(t_app *app)
{
	int 	rt;
	int		rt2;
	char	*cmd;
	pid_t	father;

	cmd = search_cmd(app);
	if (!cmd)
	{
		ft_putendl("Cette commande en'existe pas");
		return ;
	}
	ft_putendl(cmd);
	father = fork();
	if (father)
	{
		rt2 = wait(&rt);
	}
	else
	{
		execve(cmd, cmd_to_tab(app) , env_to_tab(app));
	}
}
