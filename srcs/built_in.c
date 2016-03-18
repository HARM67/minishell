/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 22:06:05 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/18 03:22:27 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_built_in(t_app *app)
{
	const t_built_in built_in[NBR_BUILTIN] = {
		{"cd", 2, *bi_cd},
		{"exit", 4, *bi_exit},
		{"quit", 4, *bi_exit},
		{"unsetenv", 8, *bi_unsetenv},
		{"setenv", 6, *bi_setenv}
	};
	ft_memcpy(app->bi_cmd, built_in, sizeof(t_built_in) * NBR_BUILTIN);
}

int		check_built_in(t_app *app)
{
	int	i;

	i = -1;
	while (++i < NBR_BUILTIN)
	{
		if (ft_strcmp(app->cur_cmd->first->command,
			app->bi_cmd[i].command) == 0)
		{
			app->bi_cmd[i].do_it(app);
			return (1);
		}
	}
	return (0);
}
