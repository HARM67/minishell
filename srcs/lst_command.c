/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 03:27:56 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/18 05:09:55 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*new_lst_command()
{
	t_command	*rt;

	rt = (t_command*)ft_memalloc(sizeof(t_command));
	if (rt == 0)
		put_error("Erreur : Allocation de memoire");
	return (rt);
}

void	insert_new_lst_command(t_app *app)
{
	t_command	*lst;

	lst = new_lst_command();
	if (!app->first_cmd)
	{
		app->first_cmd = lst;
		app->last_cmd = lst;
		app->cur_cmd = lst;
	}
	else
	{
		app->last_cmd->next = lst;
		lst->previous = app->last_cmd;
		app->last_cmd = lst;
		app->cur_cmd = lst;
	}
	app->token = 0;
	app->nbr_cmd++;
}

void	clean_lst_command(t_app *app)
{
	t_command	*tmp;
	t_command	*tmp2;

	tmp = app->first_cmd;
	while (tmp)
	{
		tmp2 = tmp->next;
		clean_cmd(tmp);
		if (tmp->cmd)
			free(tmp->cmd);
		free(tmp);
		tmp = tmp2;
	}
	app->first_cmd = 0;
	app->last_cmd = 0;
	app->cur_cmd = 0;
	app->nbr_cmd = 0;
}
