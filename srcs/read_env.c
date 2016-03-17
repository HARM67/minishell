/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfroehly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 13:08:57 by mfroehly          #+#    #+#             */
/*   Updated: 2016/03/17 21:29:38 by mfroehly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem_env	*new_env(t_app *app, char *line)
{
	t_elem_env	*rt;
	int			i;
	int			j;

	i = -1;
	j = 0;
	rt = (t_elem_env*)ft_memalloc(sizeof(t_elem_env));
	if (rt == 0)
		put_error("Erreur : Allocation de memoire");
	while (line[++i] != '=')
	{
		if (line[i] == '\0')
			put_error("Erreur : environement mal formate");
		rt->name[i] = line[i];
	}
	rt->name[i] = '\0';
	while (line[++i] != '\0')
	{
		rt->content[j] = line[i];
		j++;
	}
	rt->content[j] = '\0';
	rt->size = i;
	return (rt);
}

void				insert_new_env(t_app *app,t_elem_env *insert)
{
	t_env		*environement;
	int			iteration;

	environement = &app->environement;
	iteration = environement->size;
	if (environement->first == 0)
	{
		environement->first = insert;
		environement->last = insert;
	}
	else
	{
		environement->last->next = insert;
		insert->previous = environement->last;
		environement->last = insert;
	}
	environement->size++;
}

void				insert_env(t_app *app)
{
	t_env		*environement;
	t_elem_env	*insert;
	int			iteration;

	environement = &app->environement;
	iteration = environement->size;
	insert = new_env(app, app->env[iteration]);
	if (environement->first == 0)
	{
		environement->first = insert;
		environement->last = insert;
	}
	else
	{
		environement->last->next = insert;
		insert->previous = environement->last;
		environement->last = insert;
	}
	environement->size++;
}

void				print_tab(char	**tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		ft_putendl(tab[i]);
}

char				**env_to_tab(t_app *app)
{
	t_elem_env	*current;
	char	**rt;
	int	i;

	i = -1;
	current = app->environement.first;
	rt = (char**)ft_memalloc(sizeof(char*) * (app->environement.size + 1));
	if (rt == 0)
		put_error("Erreur : Allocation memoire");
	while (++i < app->environement.size && current)
	{
		rt[i] = (char*)ft_memalloc(sizeof(char) * (current->size + 1));
		if (rt[i] == 0)
			put_error("Erreur : Allocation memoire");
		ft_strcpy(rt[i], current->name);
		ft_strcat(rt[i], "=");
		ft_strcat(rt[i], current->content);
		current = current->next;
	}
	return (rt);
}

void				print_env(t_app *app)
{
	t_elem_env		*elm;

	elm = app->environement.first;
	while (elm)
	{
		ft_putstr(elm->name);
		ft_putchar(' ');
		ft_putendl(elm->content);
		elm = elm->next;
	}
}

void				read_env(t_app *app)
{
	int	i;

	i = -1;
	while (app->env[++i])
		insert_env(app);
}
