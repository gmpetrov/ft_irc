/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:17:46 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/21 21:55:47 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netinet/in.h>
#include "client.h"

void	input(int sock)
{
	char	*line;

	get_next_line(STDIN_FILENO, &line);
	write_server(sock, line);
	free(line);
}

int		output(int sock)
{
	char	buf[BUF_SIZE];
	int		r;

	r = read_server(sock, buf);
	if (r == 0)
	{
		ft_putstr("\033[31mServer disconnected\033[0m\n");
		return (-1);
	}
	ft_putstr(buf);
	write(1, "\n", 1);
	return (0);
}

void	action(int sock)
{
	fd_set	readfd;
	int		ret;

	write_server(sock, "New Client Connected");
	while (42)
	{
		FD_ZERO(&readfd);
		FD_SET(STDIN_FILENO, &readfd);
		FD_SET(sock, &readfd);
		if ((ret = select(sock + 1, &readfd, NULL, NULL, NULL)) < 0)
			error_exit("select() problem");
		if (FD_ISSET(STDIN_FILENO, &readfd))
			input(sock);
		else if (FD_ISSET(sock, &readfd))
		{
			if (output(sock) == -1)
				break ;
		}
	}
}

int		main(int ac, char **av)
{
	int		port;
	int		sock;

	if (ac != 3)
	{
		ft_putstr("[USAGE] - ./client [address] [port]\n");
		return (0);
	}
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	action(sock);
	close(sock);
	return (0);
}
