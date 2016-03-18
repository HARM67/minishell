/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 23:05:55 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/18 03:22:04 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_setenv(t_app *app)
{
	t_elem_env	*tmp;
	char		*tmp2;

	if (app->cur_cmd->size != 3)
		return ;
	tmp = get_env(app, app->cur_cmd->first->next->command);
	if (tmp)
	{
		ft_bzero(tmp->content, ENV_CONTENT_LENGTH);
		ft_strcpy(tmp->content, app->cur_cmd->last->command);
	}
	else
	{
		ft_sprintf(&tmp2, "%s=%s", app->cur_cmd->first->next->command,
				app->cur_cmd->last->command);
		insert_new_env(app, new_env(app, tmp2));
		free(tmp2);
	}

}
