/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 22:06:05 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/16 22:20:29 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_built_in(t_app *app)
{
	const t_built_in built_in[NBR_BUILTIN] = {
		{"exit",4, *bi_exit}
	};
	ft_memcpy(app->bi_cmd, built_in, sizeof(t_built_in) * NBR_BUILTIN);
}

int		check_built_in(t_app *app)
{
	int	i;

	i = -1;
	while (++i < NBR_BUILTIN)
	{
		if (ft_strncmp(app->lst_cmd.first->command,
			app->bi_cmd[i].command, app->bi_cmd[i].size) == 0)
		app->bi_cmd[i].do_it(app);
	}
	return (0);
}
