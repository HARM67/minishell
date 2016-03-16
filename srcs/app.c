/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 12:58:56 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/16 22:16:30 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_app(t_app *app)
{
	read_env(app);
	init_built_in(app);
}

void	run_app(t_app *app)
{
	while (!app->stop)
	{
		get_next_line(0, &app->str_cur_cmd);
		decode_command(app);
		check_built_in(app);
	}
	/*
	int rt;
	int	rt2;
	pid_t	father;

	father = fork();
	if (father)
	{
		rt2 = wait(&rt);
		ft_printf("Je suis le pere et le pid de mon fils est %d et il m'a r'envoye %d\n", father, rt);
	}
	else
	{
		sleep(1);
		ft_printf("Je suis le fils\n");
	}
	*/
}
