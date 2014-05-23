/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:17:46 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/22 20:38:05 by gpetrov          ###   ########.fr       */
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
	char	*join;

	s1 = ft_strdup("\033[32m[");
	s2 = ft_strdup(*login);
	join = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	s2 = ft_strdup("] said \033[0m\n");
	s1 = ft_strjoin(join, s2);
	free(join);
	free(s2);
	write_server(sock, s1);
	free(s1);
}

void	nick(int sock, char *line, char **login)
{
	char	**tab;
	// char	*join;

	tab = ft_strsplit(line, ' ');
	if (tab[1] && !tab[2] && (ft_strlen(tab[1]) <= 9))
	{
		free(*login);
		*login = ft_strdup(tab[1]);
		write_server(sock, line);
		// write_server(sock, *login);
	}
	else
		write(1, "\033[31mWrong argument\033[0m\n", 24);
	free_tab(&tab);
}

int 	string_is_nb(char *str)
{
	int 	i;

	i = 0;
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);	
}

void	join(int sock, char *line, int *chan)
{
	char	**tab;
	// char	buf[BUF_SIZE];

	tab = ft_strsplit(line, ' ');
	if (tab[1] && !tab[2] && (ft_strlen(tab[1]) <= 6) && (string_is_nb(tab[1])) == 0)
	{
		write_server(sock, line);
		*chan = ft_atoi(tab[1]);
	}
	else
		write(1, "\033[31mWrong argument\033[0m\n", 24);
	free_tab(&tab);
}

void	leave(int sock, char *line, int *chan)
{
	char	**tab;
	// char 	buf[BUF_SIZE];

	tab = ft_strsplit(line, ' ');
	if (tab[1] && !tab[2] && (ft_strlen(tab[1]) <= 6) && (string_is_nb(tab[1])) == 0 && (ft_atoi(tab[1]) == *chan))
	{
		write_server(sock, "/leave");
		// read_server(sock, buf);
		write_server(sock, tab[1]);
		*chan = DEF_CHAN;
	}
	else
		write(1, "\033[31mWrong argument\033[0m\n", 24);
	free_tab(&tab);
}

char	*join_row(char **tab, int start)
{
	char	*swap;

	int 	i;

	i = start;
	if (tab[i + 1])
		swap = ft_strjoin(tab[i], tab[i + 1]);
	i++;
	while (tab[i])
	{
		if (tab[i + 1])
		{
			swap = ft_strjoin(swap, " ");
			swap = ft_strjoin(swap, tab[i + 1]);
		}
		i++;
	}
	return (swap);
}

void	msg(int sock, char *line)
{
	char	**tab;

	tab = ft_strsplit(line, ' ');
	if (tab[1] && tab[2])
		write_server(sock, line);
	else
		write(1, "\033[31mWrong argument\033[0m\n", 24);
	free_tab(&tab);
}

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
	char	*join;

	join = ft_strjoin(login, " joined the room");
	return (join);
}

void	action(int sock, char **env)
{
	fd_set	readfd;
	int		ret;
	char	*name;
	char	*join;
	char	buf[BUF_SIZE];
	int 	chan;

	chan = DEF_CHAN;
	name = get_name(env);
	join = joined_the_room(name);
	write_server(sock, name);
	read_server(sock, buf);
	ft_putstr(buf);
	write_server(sock, join);
	free(join);
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
