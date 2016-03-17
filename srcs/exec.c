/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:44:33 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/17 17:22:27 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_app *app)
{
	int rt;
	int	rt2;
	char tab[] = {"/bin/ls", "-l"};
	pid_t	father;

	father = fork();
	if (father)
	{
		rt2 = wait(&rt);
	}
	else
	{
		execve("/bin/ls", tab, app->env);
	}
}
