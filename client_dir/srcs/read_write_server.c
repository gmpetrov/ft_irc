/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_server.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 21:49:52 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/21 21:50:51 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include "client.h"

void	write_server(int sock, char *buf)
{
	char	*to_send;

	to_send = ft_strjoin(buf, END_SEND);
	if (send(sock, to_send, ft_strlen(to_send), 0) < 0)
	{
		ft_putstr("\033[31msend() error\033[0m\n");
		exit(0);
	}
}

int		read_server(int sock, char *buf)
{
	int		r;

	if ((r = recv(sock, buf, BUF_SIZE - 1, 0)) < 0)
	{
		ft_putstr("\033[31mread_server() error\033[0m\n");
		exit(0);
	}
	buf[r] = 0;
	return (r);
}
