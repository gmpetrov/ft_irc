/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:19:58 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/17 20:45:24 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

/*
**	MACRO
*/

# define NL		"\006"
# define END	"\007"
# define GET	"\005"
# define END_GET "\004"

# include<fcntl.h>
# include<sys/stat.h>
# include <dirent.h>
# include <sys/socket.h>
# include <netdb.h>
# include <sys/stat.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "libft.h"

/*
**	STRUCT
*/
# include "struct.h"

/*
**	PROTOTYPES
*/

/*
**	main.c
*/
void	do_fork(t_data data, int sock);
void	action(t_data *data);
int		create_server(int port);

/*
**	tools.c
*/
void	free_tab(char ***tab);
void	error_not_found(int cs);
void	quit(int cs, char *buf);
t_pwd	*pwd_init(void);

/*
**	pwd.c
*/
void	pwd(int cs, char *buf);

/*
**	cd.c
*/
void	cd_folder(int cs, char *limit, char *path);
void	cd(int cs, char *buf, char *limit);

/*
**	ls.c
*/
void	ls(int cs, char *buf);

/*
**	get.c
*/
void	get(int cs, char *buf);

#endif
