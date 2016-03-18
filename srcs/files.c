/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 06:22:00 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/18 06:44:26 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_file_char(char c)
{
	if (ft_isprint(c) && c != '/' && c != '\\' && c != '?' && c != '%' &&
			c != '*' && c != ':' && c != '|' && c != '"' && c != '<' &&
			c != '>')
		return (1);
	return (0);
}

static t_file_out	*new_file_out(char	*filename)
{
	t_file_out	*rt;

	rt = (t_file_out*)ft_memalloc(sizeof(t_file_out));
	if (rt == 0)
		put_error("Error can't malloc");
	ft_strcpy(rt->filename, filename);
	return (rt);
}

void	insert_file_out(t_file_lst *lst, char	*filename)
{
	t_file_out	*insert;

	insert = new_file_out(filename);
	if (!lst->first_out)
	{
		lst->first_out = insert;
		lst->last_out = insert;
	}
	else
	{
		lst->last_out->next = insert;
		insert->previous = lst->last_out;
		lst->last_out  = insert;
	}
	lst->nbr_out++;
}

void	clean_file_lst(t_file_lst *lst)
{
	t_file_out	*out;
	t_file_out	*out2;
	t_file_in	*in;
	t_file_in	*in2;

	in = lst->first_in;
	out = lst->first_out;
	while (out)
	{
		out2 = out->next;
		free(out);
		out = out2;
	}
	while (in)
	{
		in2 = in->next;
		free(in);
		in = in2;
	}
}
