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
#include <stdio.h>
#include <unistd.h>
#include "serveur.h"

void	client_write(t_env *e, int cs)
{
	int		i;
	char	*s1;
	char	*s2;
	char	*join;

	i = 0;
	s1 = ft_strdup("\033[32m[");
	s2 = ft_strdup(e->fds[cs].name);
	join = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	s2 = ft_strdup("] said ->\033[0m ");
	s1 = ft_strjoin(join, s2);
	free(join);
	free(s2);
	s1 = ft_strjoin(s1, e->fds[cs].buf_write);
	while (i < e->maxfd)
	{
		if ((e->fds[i].type == FD_CLIENT) &&
			(e->fds[i].chan == e->fds[cs].chan) && (i != cs))
			send(i, s1, ft_strlen(s1), 0);
		i++;
	}
	ft_bzero(e->fds[cs].buf_write, BUF_SIZE);
	free(s1);
}
