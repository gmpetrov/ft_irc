/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 22:13:57 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/21 22:14:03 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	main_loop(t_env *e)
{
	int 	i;

	i = 0;
	while (i < e->maxfd)
	{
		e->fds[i].chan = DEF_CHAN;
		e->fds[i].first = 0;
		e->fds[i].name = NULL;
		i++;	
	}
	while (1)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}
