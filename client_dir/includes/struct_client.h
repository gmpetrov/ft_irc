/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_client.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/19 20:30:02 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/19 21:05:00 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_CLIENT_H
# define STRUCT_CLIENT_H

# include "client.h"

typedef struct		s_client
{
	int			sock;
	char		name[BUF_SIZE];
}					t_client;

#endif
