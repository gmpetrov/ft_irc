/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/21 22:05:13 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/22 17:51:05 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include <sys/select.h>
# include "libft.h"

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define END_SEND	"\007"
# define DEF_CHAN	0;

# define BUF_SIZE	4096

# define Xv(err,res,str)	(x_void(err,res,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

typedef struct	struct_fd
{
	int			type;
	void		(*fct_read)();
	void		(*fct_write)();
	char		buf_read[BUF_SIZE + 1];
	char		buf_write[BUF_SIZE + 1];
	int			chan;
	char		*name;
	int 		first;
}				t_fd;

typedef struct	s_env
{
	t_fd		*fds;
	int			port;
	int			maxfd;
	int			max;
	int			r;
	fd_set		fd_read;
	fd_set		fd_write;
}				t_env;

void	init_env(t_env *e);
void	get_opt(t_env *e, int ac, char **av);
void	main_loop(t_env *e);
void	srv_create(t_env *e, int port);
void	srv_accept(t_env *e, int s);
void	client_read(t_env *e, int cs);
void	client_write(t_env *e, int cs);
void	clean_fd(t_fd *fd);
int		x_int(int err, int res, char *file, int line);
void	*x_void(void *err, void *res, char *file, int line);
void	init_fd(t_env *e);
void	do_select(t_env *e);
void	check_fd(t_env *e);

#endif
