/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 22:05:13 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/23 20:25:44 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H
# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define END_SEND	"\007"
# define DEF_CHAN	0;
# define BUF_SIZE	4096
# define XV(err,res,str)	(x_void(err,res,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)
# define USAGE		"Usage: %s port\n"

# include "libft.h"
# include "struct_serv.h"

void	init_env(t_env *e);
void	get_opt(t_env *e, int ac, char **av);
void	main_loop(t_env *e);
void	srv_create(t_env *e, int port);
void	srv_accept(t_env *e, int s);
void	client_read(t_env *e, int cs);
int		count_row(char **tab);
void	client_write(t_env *e, int cs);
void	clean_fd(t_fd *fd);
int		x_int(int err, int res, char *file, int line);
void	*x_void(void *err, void *res, char *file, int line);
void	init_fd(t_env *e);
void	do_select(t_env *e);
void	check_fd(t_env *e);
/*
**	cmd.c
*/
void	cmd_nick(t_env *e, int cs);
void	cmd_join(t_env *e, int cs);
void	cmd_leave(t_env *e, int cs);
void	cmd_msg(t_env *e, int cs);
void	cmd_who(t_env *e, int cs);

#endif
