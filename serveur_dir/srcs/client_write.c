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
	int		r;

	i = 0;
	r = recv(cs, e->fds[cs].buf_write, BUF_SIZE, 0);
	write(1, "fuck fuck duck\n", 15);
	while (i < e->maxfd)
	{
		write(1, "nul\n", 4);
		if ((e->fds[i].type == FD_CLIENT) && (i != cs))
			send(i, e->fds[cs].buf_write, r, 0);
		i++;
	}
}