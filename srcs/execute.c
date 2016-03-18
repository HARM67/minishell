/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:44:43 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/18 03:20:35 by mfroehly         ###   ########.fr       */
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
		if (ft_strcmp(d->d_name, app->cur_cmd->first->command) == 0)
		{
			ft_sprintf(&tmp, "%s/%s", path, app->cur_cmd->first->command);
			stat(tmp, &m_stat);
			if (m_stat.st_mode & 0111)
			{
				closedir(dirp);
				return (tmp);
			}
		}
	closedir(dirp);
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
	if (!cmd )
	{
		ft_putendl("Pas de PATH");
		return (0);
	}
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
	ft_printf("minishell: command not found: %s\n",
			app->cur_cmd->first->command);
	return (0);
}

char	*check_cmd(t_app *app)
{
	t_stat			m_stat;

	stat(app->cur_cmd->first->next->command, &m_stat);
	if (m_stat.st_mode & 0111)
		return (ft_strdup(app->cur_cmd->first->command));
	ft_printf("minishell: no such file or directory: %s\n", 
			app->cur_cmd->first->command);
	return (0);
}

void	execute(t_app *app)
{
	int 	rt;
	int		rt2;
	char	*cmd;
	pid_t	father;
	char	tmp[256];

	if (app->cur_cmd->first->command[0] == '.' || 
		app->cur_cmd->first->command[0] == '/')
		cmd = check_cmd(app);
	else
		cmd = search_cmd(app);
	if (!cmd)
		return ;
	father = fork();
	if (father)
	{
		free(cmd);
		rt2 = wait(&rt);
	}
	else
	{
		ft_printf("%d %s\n", execve(cmd, cmd_to_tab(app) , env_to_tab(app)), cmd);
	}
}
