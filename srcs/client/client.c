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

int	main(int ac, char **av)
{
	int		i;
	int		pid;

	if (ac != 3)
		return (1);
	pid = ft_atoi(av[1]);
	i = 0;
	while (1)
	{
		if (send_sig(&av[2][0], pid))
			return (1);
		i += 1;
		if (i == 8)
		{
			i = 0;
			av[2] += 1;
			if (!av[2][0])
				return (0);
		}
	}
}
