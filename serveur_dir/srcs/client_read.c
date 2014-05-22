/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 22:07:45 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/21 22:08:26 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include "serveur.h"

void	buf_copy(t_env *e, int r, int cs)
{
	int		i;

	i = 0;
	while (i <= r)
	{
		e->fds[cs].buf_write[i] = e->fds[cs].buf_read[i];
		i++;		
	}
	e->fds[cs].buf_write[i] = 0;
	ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
}

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;
	char *nick;

	i = 0;
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[r] = 0;
	ft_putstr(e->fds[cs].buf_read);
	write(1, "\n", 1);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else if (e->fds[cs].first == 0)
	{
		e->fds[cs].name = ft_strdup(e->fds[cs].buf_read);
		e->fds[cs].first = -1;
		send(cs, "User Accepted\n", 14, 0);
	}
	else if (ft_strstr(e->fds[cs].buf_read, "/nick") != NULL)
	{
		send(cs, "OK\n", 3, 0);
		free(e->fds[cs].name);
		r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
		e->fds[cs].buf_read[r] = 0;
		e->fds[cs].name	= ft_strdup(e->fds[cs].buf_read);
	}
	else if (ft_strstr(e->fds[cs].buf_read, "/join") != NULL)
	{
		send(cs, "OK\n", 3, 0);
		ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
		r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
		e->fds[cs].buf_read[r] = 0;
		e->fds[cs].chan = ft_atoi(e->fds[cs].buf_read);
	}
	else if (ft_strstr(e->fds[cs].buf_read, "/leave") != NULL)
	{
		send(cs, "OK\n", 3, 0);
		r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
		e->fds[cs].buf_read[r] = 0;
		e->fds[cs].chan = DEF_CHAN;
	}
	else if (ft_strstr(e->fds[cs].buf_read, "/msg") != NULL)
	{
		send(cs, "OK\n", 3, 0);
		r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
		e->fds[cs].buf_read[r] = 0;
		nick = ft_strdup(e->fds[cs].buf_read);
		send(cs, "OK\n", 3, 0);
		r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
		e->fds[cs].buf_read[r] = 0;
		ft_putstr("TEST\n");
		while (i < e->maxfd)
		{
			if (e->fds[i].type == FD_CLIENT && (ft_strcmp(nick, e->fds[i].name) == 0) && (i != cs))
				send(i, e->fds[cs].buf_read, r, 0);
			i++;
		}
	}
	else if (ft_strstr(e->fds[cs].buf_read, "/who") != NULL)
	{
		write(1, "OK\n", 3);
		while (i < e->maxfd)
		{
			if (e->fds[i].type == FD_CLIENT && (i != cs))
			{
				send(cs, e->fds[i].name, ft_strlen(e->fds[i].name), 0);
				send(cs, "\n", 1, 0);
			}
			i++;
		}
	}
	else
	{
		// buf_copy(e, r, cs);
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) && (e->fds[i].chan == e->fds[cs].chan) && (i != cs))
				send(i, e->fds[cs].buf_read, r, 0);
			i++;
		}
	}
	ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
}
