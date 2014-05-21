/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:16:38 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/21 21:53:16 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/*
**	MACRO
*/
# define BUF_SIZE		1024
# define END			"\007"
# define NL				"\006"
# define GET			"\005"
# define END_GET		"\004"

# include "libft.h"

/*
**	Prototypes
*/

/*
**	tools.c
*/
void	action(int sock);
void	error_exit(char *str);
/*
**	read_write_server.c
*/
int		read_server(int sock, char *buf);
void	write_server(int sock, char *buf);

/*
**	main.c
*/
int		output(int sock);
void	input(int sock);
int		create_client(char *addr, int port);
void	free_tab(char ***tab);

#endif
