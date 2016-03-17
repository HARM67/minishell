/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 12:58:56 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/17 19:21:59 by mfroehly         ###   ########.fr       */
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
	ft_strcpy(app->prompt, "\033[32;2mminishell\033[31m>\033[0m");
	read_env(app);
	init_built_in(app);
	signal(SIGTSTP, *sig_interupt);
	signal(SIGINT, *sig_kill);
}

void	run_app(t_app *app)
{
	while (!app->stop)
	{
		print_prompt(app);
		get_next_line(0, &app->str_cur_cmd);
		decode_command(app);
		if (!app->lst_cmd.size)
			continue ;
		if (!check_built_in(app))
			execute(app);
	}
}
