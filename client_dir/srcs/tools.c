/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 21:45:10 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/23 20:41:02 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "client.h"

void	free_tab(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

void	error_exit(char *str)
{
	printf("\033[31m%s\033[0m\n", str);
	exit(0);
}

int		string_is_nb(char *str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

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
