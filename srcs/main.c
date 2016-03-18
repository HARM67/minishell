/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 12:57:48 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/18 01:59:08 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	app.ac = ac;
	app.av = av;
	app.env = env;
	init_app(&app);
	run_app(&app);
	return (0);
}
