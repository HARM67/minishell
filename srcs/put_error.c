/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:11:21 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/19 01:16:02 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void	put_error_cmd(t_app *app, char	*str)
{
	ft_putendl_fd(str, 1);
	app->token = 0;
	app->bad_cmd = 1;
}
