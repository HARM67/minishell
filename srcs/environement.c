/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:10:29 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/17 17:22:27 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem_env	*get_env(t_app *app, char *env)
{
	t_elem_env	*tmp;

	tmp = app->environement.first;
	while(tmp)
	{
		if (ft_strcmp(tmp->name, env) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}
