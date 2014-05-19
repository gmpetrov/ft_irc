/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 20:40:32 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/17 19:02:33 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

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

void	error_not_found(int cs)
{
	send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
	send(cs, "Command not found\n", 19, MSG_OOB);
}

void	quit(int cs, char *buf)
{
	(void)buf;
	send(cs, "\033[32mSUCCESS\033[0m\n", 19, MSG_OOB);
	send(cs, NL, 2, MSG_OOB);
}

t_pwd	*pwd_init(void)
{
	static t_pwd	*pwd = NULL;

	if (pwd == NULL)
	{
		pwd = (t_pwd *)malloc(sizeof(t_pwd));
		pwd->test = 1;
	}
	return (pwd);
}
