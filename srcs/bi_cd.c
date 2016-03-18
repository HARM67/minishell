/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 23:23:43 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/18 03:21:14 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_cd(t_app *app)
{
	t_elem_env	*home;

	if (app->cur_cmd->size == 2)
		if(chdir(app->cur_cmd->first->next->command) == -1)
			ft_printf("cd: no such file or directory: %s\n",
					app->cur_cmd->first->next->command);
	if (app->cur_cmd->size == 1)
	{
		home = get_env(app, "HOME");
		if(chdir(home->content) == -1)
			ft_printf("cd: no such file or directory: %s\n",
					home->content);
	}
}
