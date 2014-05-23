/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:17:46 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/23 20:40:24 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "client.h"

void	input(int sock, char **login, int *chan)
{
	char	*line;

	if (get_next_line(STDIN_FILENO, &line) <= 0)
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strncmp(line, "/nick", 5) == 0)
		nick(sock, line, login);
	else if (ft_strncmp(line, "/join", 5) == 0)
		join(sock, line, chan);
	else if (ft_strncmp(line, "/leave", 6) == 0)
		leave(sock, line, chan);
	else if (ft_strncmp(line, "/msg", 4) == 0)
		msg(sock, line);
	else if (ft_strcmp(line, "") == 0)
	{
		free(line);
		return ;
	}
	else
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
	write(1, "\n", 1);
	ft_putstr(buf);
	write(1, "\n", 1);
	return (0);
}

void	init_action(int sock, char *name)
{
	char	*join;
	char	buf[BUF_SIZE];

	join = joined_the_room(name);
	write_server(sock, name);
	read_server(sock, buf);
	ft_putstr(buf);
	write_server(sock, join);
	free(join);
}

void	action(int sock, char **env)
{
	fd_set	readfd;
	int		ret;
	char	*name;
	int		chan;

	chan = DEF_CHAN;
	name = get_name(env);
	init_action(sock, name);
	while (42)
	{
		prompt(name);
		FD_ZERO(&readfd);
		FD_SET(STDIN_FILENO, &readfd);
		FD_SET(sock, &readfd);
		if ((ret = select(sock + 1, &readfd, NULL, NULL, NULL)) < 0)
			error_exit("select() problem");
		if (FD_ISSET(STDIN_FILENO, &readfd))
			input(sock, &name, &chan);
		else if (FD_ISSET(sock, &readfd))
		{
			if (output(sock) == -1)
				break ;
		}
	}
}

int		main(int ac, char **av, char **env)
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
	action(sock, env);
	close(sock);
	return (0);
}
