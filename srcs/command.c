/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:46:50 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/18 03:24:07 by mfroehly         ###   ########.fr       */
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
	if (!app->cur_cmd->first)
	{
		app->cur_cmd->first = new;
		app->cur_cmd->last = new;
	}
	else
	{
		app->cur_cmd->last->next = new;
		new->previous = app->cur_cmd->last;
		app->cur_cmd->last = new;
	}
	app->cur_cmd->size++;
}

void	cmd_token_0(t_app *app, char c)
{
	if (c != ' ' && c != '\t')
	{
		insert_new_command(app);
		if (c == '"')
		{
			app->cur_cmd->token = 2;
		}
		else if (c != '$' && c != '~')
		{
			app->cur_cmd->last->command[app->cur_cmd->last->size] = c;
			app->cur_cmd->last->size++;
			app->cur_cmd->token = 1;
		}
		else if (c == '$')
			app->cur_cmd->token = 3;
		else if (c == '~')
			app->cur_cmd->token = 5;
	}
}

void	clean_cmd(t_app *app)
{
	t_elem_command	*elm;
	t_elem_command	*elm2;

	elm = app->cur_cmd->first;
	while (elm)
	{
		elm2 = elm->next;
		free(elm);
		elm = elm2;
	}
}

void	cmd_token_1(t_app *app, char c)
{
	if (c != ' ' && c != '\t' && c != '$' && c != '~')
	{
		app->cur_cmd->last->command[app->cur_cmd->last->size] = c;
		app->cur_cmd->last->size++;
	}
	else if (c == '$')
		app->cur_cmd->token = 3;
	else
		app->cur_cmd->token = 0;
}

void	cmd_token_2(t_app *app, char c)
{
	if (c != '"' && c != '$' && c != '~')
	{
		app->cur_cmd->last->command[app->cur_cmd->last->size] = c;
		app->cur_cmd->last->size++;
	}
	else if (c == '$')
		app->cur_cmd->token = 4;
	else
		app->cur_cmd->token = 0;
}

void	cmd_token_3_4(t_app *app, char c)
{
	int		i;
	t_elem_env	*tmp2;
	char	*tmp;

	if (ft_isalnum(c))
		app->cur_cmd->env_find[app->cur_cmd->env_find_tmp++] = c;
	else
	{
		i = -1;
		tmp2 = get_env(app, app->cur_cmd->env_find);
		if (tmp2)
		{
			tmp = tmp2->content;
			while (*tmp)
			{
				app->cur_cmd->last->command[app->cur_cmd->last->size] = *tmp;
				tmp++;
				app->cur_cmd->last->size++;
			}
		}
		app->cur_cmd->env_find_tmp = 0;
		ft_bzero(app->cur_cmd->env_find, ENV_NAME_LENGTH);
		if ((app->cur_cmd->token == 3 && (c == ' ' || c == '\t')) ||
				(app->cur_cmd->token == 4 && c == '"'))
			app->cur_cmd->token = 0;
		else
		{
			app->cur_cmd->token -= 2;
		if (app->cur_cmd->token == 1)
			cmd_token_1(app, c);
		else if (app->cur_cmd->token == 2)
			cmd_token_2(app, c);
		}
	}
}

void	print_lst_cmd(t_app *app)
{
	t_elem_command *elm;

	elm = app->cur_cmd->first;
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
	rt = (char**)ft_memalloc(sizeof(char*) * (app->cur_cmd->size + 1));
	elm = app->cur_cmd->first;
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
	
	lst_command = app->cur_cmd;
	if (lst_command->token == 0)
	{
		clean_cmd(app);
		ft_bzero(lst_command, sizeof(t_command));
	}
	command = app->str_cur_cmd;
	while (*command)
	{
		if (lst_command->token == 0)
			cmd_token_0(app, *command);
		else if (lst_command->token == 1)
			cmd_token_1(app, *command);
		else if (lst_command->token == 2)
			cmd_token_2(app, *command);
		else if (lst_command->token == 3 || lst_command->token == 4)
			cmd_token_3_4(app, *command);
		command++;
	}
	if (lst_command->token == 3 || lst_command->token == 4)
	{
		cmd_token_3_4(app, *command);
		lst_command->token = 0;
	}
	if (lst_command->token == 1)
		lst_command->token = 0;
	if (lst_command->token == 2)
	{
		app->cur_cmd->last->command[app->cur_cmd->last->size] = '\n';
		app->cur_cmd->last->size++;
	}
}
