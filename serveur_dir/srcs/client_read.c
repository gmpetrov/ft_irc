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

int		count_row(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	close_client(t_env *e, int cs)
{
	close(cs);
	clean_fd(&e->fds[cs]);
	printf("client #%d gone away\n", cs);
}

void	get_name(t_env *e, int cs)
{
	int		r;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[r] = 0;
	e->fds[cs].name = ft_strdup(e->fds[cs].buf_read);
	e->fds[cs].first = -1;
	send(cs, "User Accepted\n", 14, 0);
}

void	msg_all(t_env *e, int cs)
{
	int		r;

	r = recv(cs, e->fds[cs].buf_write, BUF_SIZE, 0);
	e->fds[cs].buf_write[r] = 0;
}

void	client_read(t_env *e, int cs)
{
	int		r;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, MSG_PEEK);
	e->fds[cs].buf_read[r] = 0;
	ft_putstr(e->fds[cs].buf_read);
	write(1, "\n", 1);
	if (r <= 0)
		close_client(e, cs);
	else if (e->fds[cs].first == 0)
		get_name(e, cs);
	else if (ft_strstr(e->fds[cs].buf_read, "/nick") != NULL)
		cmd_nick(e, cs);
	else if (ft_strstr(e->fds[cs].buf_read, "/join") != NULL)
		cmd_join(e, cs);
	else if (ft_strstr(e->fds[cs].buf_read, "/leave") != NULL)
		cmd_leave(e, cs);
	else if (ft_strstr(e->fds[cs].buf_read, "/msg") != NULL)
		cmd_msg(e, cs);
	else if (ft_strstr(e->fds[cs].buf_read, "/who") != NULL)
		cmd_who(e, cs);
	else
		msg_all(e, cs);
	ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
}
