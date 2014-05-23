/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 20:24:44 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/23 20:24:48 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include "serveur.h"

void	cmd_nick(t_env *e, int cs)
{
	char	**tab;
	int		r;

	free(e->fds[cs].name);
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[r] = 0;
	tab = ft_strsplit(e->fds[cs].buf_read, ' ');
	if (tab[1])
		e->fds[cs].name = ft_strdup(tab[1]);
}

void	cmd_join(t_env *e, int cs)
{
	char	**tab;
	int		r;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[r] = 0;
	tab = ft_strsplit(e->fds[cs].buf_read, ' ');
	if (tab[1])
		e->fds[cs].chan = ft_atoi(tab[1]);
}

void	cmd_leave(t_env *e, int cs)
{
	int		r;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[r] = 0;
	e->fds[cs].chan = DEF_CHAN;
}

void	cmd_msg(t_env *e, int cs)
{
	int		r;
	char	**tab;
	char	*nick;
	int		i;

	i = 0;
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[r] = 0;
	tab = ft_strsplit(e->fds[cs].buf_read, ' ');
	if (count_row(tab) < 3)
		return ;
	if (tab[1])
		nick = ft_strdup(tab[1]);
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT &&
			(ft_strcmp(nick, e->fds[i].name) == 0) && (i != cs))
			send(i, e->fds[cs].buf_read + 6 + ft_strlen(nick),
				ft_strlen(e->fds[cs].buf_read), 0);
		i++;
	}
}

void	cmd_who(t_env *e, int cs)
{
	int		r;
	int		i;

	i = 0;
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[r] = 0;
	while (i < e->maxfd)
	{
		if (e->fds[i].type == FD_CLIENT &&
			(e->fds[cs].chan == e->fds[i].chan) && (i != cs))
		{
			send(cs, e->fds[i].name, ft_strlen(e->fds[i].name), 0);
			send(cs, "\n", 1, 0);
		}
		i++;
	}
}
