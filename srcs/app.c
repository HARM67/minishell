/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 12:58:56 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/17 17:22:52 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_app(t_app *app)
{
	ft_strcpy(app->prompt, "minishell");
	read_env(app);
	init_built_in(app);
}

void	run_app(t_app *app)
{
	while (!app->stop)
	{
		ft_putstr(app->prompt);
		ft_putchar('>');
		get_next_line(0, &app->str_cur_cmd);
		decode_command(app);
		check_built_in(app);
		execute(app);
	}
}
