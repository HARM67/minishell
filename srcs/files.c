/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 06:22:00 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/19 02:13:27 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_file_char(char c)
{
	if (ft_isprint(c) && c != '/' && c != '\\' && c != '?' && c != '%' &&
			c != '*' && c != ':' && c != '|' && c != '"' && c != '<' &&
			c != '>' && c != ' ')
		return (1);
	return (0);
}

static t_file_in	*new_file_in()
{
	t_file_in	*rt;

	rt = (t_file_in*)ft_memalloc(sizeof(t_file_in));
	if (rt == 0)
		put_error("Error can't malloc");
	return (rt);
}

void	insert_file_in(t_file_lst *lst)
{
	t_file_in	*insert;

	insert = new_file_in();
	if (!lst->first_in)
	{
		lst->first_in = insert;
		lst->last_in = insert;
	}
	else
	{
		lst->last_in->next = insert;
		insert->previous = lst->last_in;
		lst->last_in  = insert;
	}
	lst->nbr_in++;
}

static t_file_out	*new_file_out()
{
	t_file_out	*rt;

	rt = (t_file_out*)ft_memalloc(sizeof(t_file_out));
	if (rt == 0)
		put_error("Error can't malloc");
	return (rt);
}

void	insert_file_out(t_file_lst *lst)
{
	t_file_out	*insert;

	insert = new_file_out();
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

void	print_files_lst(t_file_lst *lst)
{
	t_file_out	*out;
	t_file_in	*in;
	int			i;

	in = lst->first_in;
	out = lst->first_out;
	i = 0;
	while (out)
	{
		ft_printf("file_out: fd : %d %s\n", out->fd, out->filename);
		out = out->next;
	}
	while (in)
	{
		ft_printf("file_in: fd : %d %s\n", in->fd, in->filename);
		in = in->next;
	}
	i = 0;
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

void	link_out_file(t_file_lst *lst)
{
	t_file_out *out;

	out = lst->first_out;
	while (out)
	{
		out->fd = open(out->filename, O_WRONLY | O_CREAT);
		fchmod(out->fd, 0644);
		dup2(out->fd, 1);
		out = out->next;
	}
}

void	link_in_file(t_file_lst *lst)
{
	int	temoin;
	t_file_in *in;

	temoin = 0;
	in = lst->first_in;
	while (in)
	{
		in->fd = open(in->filename, O_RDONLY);
		dup2(in->fd, temoin);
		temoin = dup(in->fd);
		in = in->next;
	}
}
