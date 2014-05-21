
#include <sys/socket.h>
#include <unistd.h>
#include "bircd.h"

void	client_write(t_env *e, int cs)
{
	// (void)cs;
	// (void)e;
	int		i;
	int		r;

	i = 0;
	r = recv(cs, e->fds[cs].buf_write, BUF_SIZE, 0);
	write(1, "fuck fuck duck\n", 15);
	while (i < e->maxfd)
	{
		write(1, "nul\n", 4);
		if ((e->fds[i].type == FD_CLIENT) && (i != cs))
			send(i, e->fds[cs].buf_write, r, 0);
		i++;
	}
}
