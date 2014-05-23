/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:16:38 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/23 20:42:28 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/*
**	MACRO
*/
# define BUF_SIZE		1024
# define END_SEND		"\007"
# define NL				"\006"
# define GET			"\005"
# define END_GET		"\004"
# define DEF_CHAN		0

# include "libft.h"

/*
**	Prototypes
*/

/*
**	tools.c
*/
void	free_tab(char ***tab);
void	error_exit(char *str);
int		string_is_nb(char *str);
void	send_id(int sock, char **login);
/*
**	read_write_server.c
*/
int		read_server(int sock, char *buf);
void	write_server(int sock, char *buf);
/*
**	main.c
*/
int		output(int sock);
void	input(int sock, char **login, int *chan);
int		create_client(char *addr, int port);
void	init_action(int sock, char *name);
void	action(int sock, char **env);
/*
**	cmd_client.c
*/
void	nick(int sock, char *line, char **login);
void	join(int sock, char *line, int *chan);
void	leave(int sock, char *line, int *chan);
char	*join_row(char **tab, int start);
void	msg(int sock, char *line);
/*
**	tools2.c
*/
char	*get_name(char **env);
void	prompt(char *login);
char	*joined_the_room(char *login);

#endif
