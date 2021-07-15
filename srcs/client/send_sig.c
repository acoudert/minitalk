#include "client.h"

char	send_sig(char *c, int pid)
{
	if (*c & 128)
	{
		if (kill(pid, SIGUSR1) < 0)
			return (1);
	}
	else if (kill(pid, SIGUSR2) < 0)
		return (1);
	*c <<= 1;
	usleep(TIME);
	return (0);
}
