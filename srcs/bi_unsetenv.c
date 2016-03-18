/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 23:07:21 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/17 23:07:25 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bi_unsetenv(t_app *app)
{
	t_elem_env	*tmp;
	char		*tmp2;

	if (app->lst_cmd.size != 2)
		return ;
	tmp = get_env(app, app->lst_cmd.first->next->command);
	if (tmp)
	{
		if (tmp->next)
			tmp->next->previous = tmp->previous;
		if (tmp->previous)
			tmp->previous->next = tmp->next;
		if (tmp == app->environement.first)
			app->environement.first = tmp->next;
	}
}
