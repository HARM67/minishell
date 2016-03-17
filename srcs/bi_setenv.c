/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 21:06:55 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/17 21:27:33 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_setenv(t_app *app)
{
	t_elem_env	*tmp;
	char		*tmp2;

	if (app->lst_cmd.size != 3)
		return ;
	tmp = get_env(app, app->lst_cmd.first->next->command);
	if (tmp)
	{
		ft_bzero(tmp->content, ENV_CONTENT_LENGTH);
		ft_strcpy(tmp->content, app->lst_cmd.last->command);
	}
	else
	{
		ft_sprintf(&tmp2, "%s=%s", app->lst_cmd.first->next->command,
				app->lst_cmd.last->command);
		insert_new_env(app, new_env(app, tmp2));
		free(tmp2);
	}

}
