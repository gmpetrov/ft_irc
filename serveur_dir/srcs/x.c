/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 22:16:05 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/21 22:26:48 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"

int		x_int(int err, int res, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "error (%s, %d): %s\n",
				file, line, strerror(errno));
		exit (1);
	}
	return (res);
}

void	*x_void(void *err, void *res, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "error (%s, %d): %s\n",
				file, line, strerror(errno));
		exit (1);
	}
	return (res);
}
