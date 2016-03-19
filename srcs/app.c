/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 12:58:56 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/19 01:09:54 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_interupt(int n)
{
	n = 0;
}

void	sig_kill(int n)
{
	n = 0;
}

void	init_app(t_app *app)
{
	getcwd(app->prompt, MAX_PROMT_LENGTH);
	read_env(app);
	init_built_in(app);
	signal(SIGTSTP, *sig_interupt);
	signal(SIGINT, *sig_kill);
//	app->cur_cmd = (t_command*)ft_memalloc(sizeof(t_command));
}

void	run_app(t_app *app)
{
	while (!app->stop)
	{
		if (app->token == 0)
		{
			app->bad_cmd = 0;
			print_prompt(app);
		}
		else if (app->token == 2)
			ft_putstr("dquote> ");
		get_next_line(0, &app->str_cur_cmd);
		if (app->str_cur_cmd == 0)
			continue ;
		decode_command(app);
		free(app->str_cur_cmd);
		if (!app->cur_cmd->size)
			continue ;
		if (app->token == 0 && !check_built_in(app))
		{
			app->cur_cmd = app->first_cmd;
			execute(app);
		}
		getcwd(app->prompt, MAX_PROMT_LENGTH);
		if (app->token == 0)
			clean_lst_command(app);
	}
}
