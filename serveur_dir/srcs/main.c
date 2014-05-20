/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:20:57 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/20 18:08:26 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include "serveur.h"

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					val;

	val = 1;
	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("\033[31mERROR\033[0m\n");
		ft_putstr("Bind problem, please try another port\n");
		exit(0);
	}
	listen(sock, 42);
	return (sock);
}

int		read_client(int cs, char *buf)
{
	int	r;

	if ((r = recv(cs, buf, BUF_SIZE - 1, 0)) < 0)
	{
		ft_putstr("\033[31mread_client()\033[0m\n");
		exit(0);
	}
	buf[r] = 0;
	return (r);
}

void	remove_client(t_client *clients, int to_remove, int *actual)
{
	memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1));
	(*actual)--;
}

void	write_client(int sock, char *buf)
{
	if (send(sock, buf, BUF_SIZE - 1, 0) < 0)
	{
		ft_putstr("\033[31mwrite_client() Error\033[0m\n");
		exit(0);
	}
}

void	send_to_all(t_client *clients, t_client sender, int actual, char *buf, char from_server)
{
	int		i;
	char	msg[] = "ce ci est un petit test\n";
//	message[0] = 0;
	i = 0;

	(void)from_server;
	(void)buf;
	while (i < actual)
	{
		if (sender.sock != clients[i].sock)
		{
			write_client(clients[i].sock, msg);			
		}
		i++;
	}
}

void	clear_clients(t_client *clients, int actual)
{
	int		i;

	i = 0;
	while (i < actual)
	{
		close(clients[i].sock);
		i++;
	}
}

void	action(/*t_data *data*/int sock)
{
	char		buf[BUF_SIZE];
	int			actual;
	int			max;
	t_client	clients[MAX_CLIENT];
	fd_set		readfd;
	int			i;

	max = sock;
	actual = 0;
	while (42)
	{/*
		data->r = read(data->cs, data->buf, 1023);
		data->buf[data->r] = 0;
		write(1, data->buf, data->r);
		write(1, "\n", 1);
		send(data->cs, END, 2, 0);
	*/
		i = 0;
		FD_ZERO(&readfd);
		FD_SET(1, &readfd);
		FD_SET(sock, &readfd);
		while (i < actual)
		{
			FD_SET(clients[i].sock, &readfd);
			i++;
		}
		if (select(max + 1, &readfd,  NULL, NULL, NULL) == -1)
		{
			ft_putstr("\033[31mselect() problem\033[0m\n");
			exit(0);	
		}
		if (FD_ISSET(1, &readfd))
		{
			break ;
		}
		else if (FD_ISSET(sock, &readfd))
		{
			struct sockaddr_in	csin = { 0 };
			socklen_t			sinsize;

			sinsize = sizeof(csin);
			int cs = accept(sock, (struct sockaddr *)&csin, &sinsize);
			if (cs == -1)
			{
				ft_putstr("\033[31maccept() ERROR\033[0m\n");
				continue ;
			}
			if (read_client(cs, buf) == -1)
			{
				continue ;
			}
			max = (cs > max ? cs : max);
			FD_SET(cs, &readfd);
			t_client c = { cs };
			clients[actual] = c;
			actual++;
			write(1, buf, ft_strlen(buf));
		}
		else
		{
			i = 0;
			while (i < actual)
			{
				if (FD_ISSET(clients[i].sock, &readfd))
				{
					t_client client = clients[i];
					int c = read_client(clients[i].sock, buf);
					if (c == 0)
					{
						close(clients[i].sock);
						send_to_all(clients, client, actual, "A client disconnected\n", 1);
					}
					else
						send_to_all(clients, client, actual, buf, 0);
					write(1, buf, ft_strlen(buf));
					break ;
				}
				i++;
			}
		}
	}
	clear_clients(clients, actual);
}
/*
void	do_fork(t_data data, int sock)
{
	data.cs = accept(sock, (struct sockaddr *)&data.csin, &data.cslen);
	if (fork() == 0)
		action(&data);
	else
		do_fork(data, sock);
}
*/
int		main(int ac, char **av)
{
	t_data				data;
	int					port;
	int					sock;
	char				buf[1024];

	if (ac != 2)
	{
		ft_putstr("[USAGE] - ./serveur [port]\n");
		return (0);
	}
	port = ft_atoi(av[1]);
	sock = create_server(port);
	data.limit = getcwd(buf, 1023);
//	do_fork(data, sock);
	action(sock);
	close(data.cs);
	close(sock);
	return (0);
}
