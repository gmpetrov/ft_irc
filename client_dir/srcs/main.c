/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:17:46 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/21 23:50:17 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "client.h"

void	send_id(int sock, char **login)
{
	char	*s1;
	char	*s2;

	s1 = ft_strdup("\033[32m[");
	s2 = ft_strdup(*login);
	s1 = ft_strcat(s1, s2);
	free(s2);
	s2 = ft_strdup("] said \033[0m\n");
	s1 = ft_strcat(s1, s2);
	write_server(sock, s1);
	free(s1);
	free(s2);
}

void	input(int sock, char **login)
{
	char	*line;
	char	**tab;

	get_next_line(STDIN_FILENO, &line);
	if (ft_strncmp(line, "/nick", 5) == 0)
	{
		tab = ft_strsplit(line, ' ');
		if (tab[1] && !tab[2] && (ft_strlen(tab[1]) <= 9))
		{
			free(*login);
			*login = ft_strdup(tab[1]);
		}
		else
			write(1, "\033[31mWrong argument\033[0m\n", 24);
		free_tab(&tab);
	}
	else
	{
		send_id(sock, login);
		write_server(sock, line);
	}
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

char	*get_name(char **env)
{
	int		i;
	int		j;
	int		k;
	char	*login;

	i = 0;
	k = 0;
	while (env[i])
	{
		if (strncmp(env[i], "LOGNAME", 7) == 0)
		{
			j = 8;
			login = (char *)malloc(sizeof(char) * ft_strlen(env[i]));
			while (env[i][j] != 0)
			{
				login[k] = env[i][j];
				k++;
				j++;
			}
			login[k] = 0;
			return (login);
		}
		i++;
	}
	return ("Default");
}

void	prompt(char *login)
{
	ft_putstr("\033[33m");
	ft_putstr("[");
	ft_putstr(login);
	ft_putstr("]");
	ft_putstr("-> \033[0m");
}

char	*joined_the_room(char *login)
{
	char	*s1;
	char	*s2;

	s1 = ft_strdup(login);
	s2 = ft_strdup(" joined the room");
	s1 = ft_strcat(s1, s2);
	free(s2);
	return (s1);
}

void	action(int sock, char **env)
{
	fd_set	readfd;
	int		ret;
	char	*name;
	char	*join;

	name = get_name(env);
	join = joined_the_room(name);
	write_server(sock, join);
	while (42)
	{
		prompt(name);
		FD_ZERO(&readfd);
		FD_SET(STDIN_FILENO, &readfd);
		FD_SET(sock, &readfd);
		if ((ret = select(sock + 1, &readfd, NULL, NULL, NULL)) < 0)
			error_exit("select() problem");
		if (FD_ISSET(STDIN_FILENO, &readfd))
			input(sock, &name);
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
