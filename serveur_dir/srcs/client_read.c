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

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;

	r = recv(cs, e->fds[cs].buf_read, BUF_SIZE, 0);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) && (i != cs))
				send(i, e->fds[cs].buf_read, r, 0);
			i++;
		}
	}
}
