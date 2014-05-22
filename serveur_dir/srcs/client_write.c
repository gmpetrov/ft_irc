/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 22:08:49 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/21 22:08:59 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <unistd.h>
#include "serveur.h"

void	client_write(t_env *e, int cs)
{
	int		i;

	i = 0;
	// r = recv(cs, e->fds[cs].buf_write, BUF_SIZE, 0);
	// write(1, "fuck fuck duck\n", 15);
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT) && (i != cs))
			send(i, e->fds[cs].buf_write, ft_strlen(e->fds[cs].buf_write), 0);
		i++;
	}
	ft_bzero(e->fds[cs].buf_write, BUF_SIZE);
}
