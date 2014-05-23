/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/23 20:41:40 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/23 20:41:44 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

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
