/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:46:50 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/16 21:49:52 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_elem_command	*new_elem_command()
{
	t_elem_command	*rt;

	rt = (t_elem_command*)ft_memalloc(sizeof(t_elem_command));
	if (rt == 0)
		put_error("Erreur : Allocation de memoire");
	return (rt);
}

void	insert_new_command(t_app *app)
{
	t_elem_command	*new;

	new = new_elem_command();
	if (!app->lst_cmd.first)
	{
		app->lst_cmd.first = new;
		app->lst_cmd.last = new;
	}
	else
	{
		app->lst_cmd.last->next = new;
		new->previous = app->lst_cmd.last;
		app->lst_cmd.last = new;
	}
	app->lst_cmd.size++;
}

void	cmd_token_0(t_app *app, char c)
{
	if (c != ' ' && c != '\t')
	{
		insert_new_command(app);
		if (c == '"')
		{
			app->lst_cmd.token = 2;
		}
		else
		{
			app->lst_cmd.last->command[app->lst_cmd.last->size] = c;
			app->lst_cmd.last->size++;
			app->lst_cmd.token = 1;
		}
	}
}

void	clean_cmd(t_app *app)
{
	t_elem_command	*elm;
	t_elem_command	*elm2;

	elm = app->lst_cmd.first;
	while (elm)
	{
		elm2 = elm->next;
		free(elm);
		elm = elm2;
	}
}

void	cmd_token_1(t_app *app, char c)
{
	if (c != ' ' && c != '\t')
	{
		app->lst_cmd.last->command[app->lst_cmd.last->size] = c;
		app->lst_cmd.last->size++;
	}
	else
		app->lst_cmd.token = 0;
}

void	cmd_token_2(t_app *app, char c)
{
	if (c != '"')
	{
		app->lst_cmd.last->command[app->lst_cmd.last->size] = c;
		app->lst_cmd.last->size++;
	}
	else
		app->lst_cmd.token = 0;
}

void	print_lst_cmd(t_app *app)
{
	t_elem_command *elm;

	elm = app->lst_cmd.first;
	while (elm)
	{
		ft_putendl(elm->command);
		elm = elm->next;
	}
}

char	**cmd_to_tab(t_app *app)
{
	char			**rt;
	t_elem_command	*elm;
	int				i;

	i = 0;
	rt = (char**)ft_memalloc(sizeof(char*) * (app->lst_cmd.size + 1));
	elm = app->lst_cmd.first;
	while (elm)
	{
		rt[i] = (char*)ft_memalloc(sizeof(char) * (elm->size + 1));
		ft_strcpy(rt[i], elm->command);
		elm = elm->next;
		i++;
	}
	return (rt);
}

void	decode_command(t_app *app)
{
	t_command	*lst_command;
	char		*command;
	
	lst_command = &app->lst_cmd;
	clean_cmd(app);
	ft_bzero(lst_command, sizeof(t_command));
	command = app->str_cur_cmd;
	while (*command)
	{
		if (lst_command->token == 0)
			cmd_token_0(app, *command);
		else if (lst_command->token == 1)
			cmd_token_1(app, *command);
		else if (lst_command->token == 2)
			cmd_token_2(app, *command);
		command++;
	}
	print_lst_cmd(app);
}