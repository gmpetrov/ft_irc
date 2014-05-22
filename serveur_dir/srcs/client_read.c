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
	// ft_bzero(e->fds[cs].buf_read, BUF_SIZE);
}

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;

	i = 0;
	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	e->fds[cs].buf_read[r] = 0;
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
		send(cs, "User Accepted\n", 1, 0);
		write(1, e->fds[cs].name, ft_strlen(e->fds[cs].name));
	}
	else if (ft_strncmp(e->fds[cs].buf_read, "/who", 4) == 0)
	{

		send(i, e->fds[i].name, ft_strlen(e->fds[i].name), 0);
	}
	else
	{
		buf_copy(e, r, cs);
		// i = 0;
		// while (i < e->maxfd)
		// {
		// 	if ((e->fds[i].type == FD_CLIENT) && (i != cs))
		// 		send(i, e->fds[cs].buf_read, r, 0);
		// 	i++;
		// }
	}
}
