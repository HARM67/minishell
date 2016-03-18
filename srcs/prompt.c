/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 19:02:51 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/18 01:06:55 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_path(char *str)
{
	while (*str)
	{
		if (*str == '/')
			ft_putstr("\033[31;1m");
		ft_putchar(*str);
		if (*str == '/')
			ft_putstr("\033[33;1m");
		str++;
	}
}

void	print_prompt(t_app *app)
{
	put_path(app->prompt);
	ft_putstr("\033[31m>\033[0m");
}
