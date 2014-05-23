/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_client.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 20:39:13 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/23 20:39:31 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	nick(int sock, char *line, char **login)
{
	char	**tab;

	tab = ft_strsplit(line, ' ');
	if (tab[1] && !tab[2] && (ft_strlen(tab[1]) <= 9))
	{
		free(*login);
		*login = ft_strdup(tab[1]);
		write_server(sock, line);
	}
	else
		write(1, "\033[31mWrong argument\033[0m\n", 24);
	free_tab(&tab);
}

void	join(int sock, char *line, int *chan)
{
	char	**tab;

	tab = ft_strsplit(line, ' ');
	if (tab[1] && !tab[2] && (ft_strlen(tab[1]) <= 6) &&
		(string_is_nb(tab[1])) == 0)
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

	tab = ft_strsplit(line, ' ');
	if (tab[1] && !tab[2] && (ft_strlen(tab[1]) <= 6) &&
		(string_is_nb(tab[1])) == 0 && (ft_atoi(tab[1]) == *chan))
	{
		write_server(sock, line);
		*chan = DEF_CHAN;
	}
	else
		write(1, "\033[31mWrong argument\033[0m\n", 24);
	free_tab(&tab);
}

char	*join_row(char **tab, int start)
{
	char	*swap;
	int		i;

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
