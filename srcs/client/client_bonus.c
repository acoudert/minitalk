#include "client.h"

void	acknowledgement(int signum)
{
	(void)signum;
	printf("Acknowledgement received\n");
}

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

char	send_container(int pid)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		if (kill(pid, SIGUSR1) < 0)
			return (1);
		i += 1;
		usleep(TIME);
	}
	return (0);
}

char	send_client_pid(int pid)
{
	int		i;
	int		c;
	char	client_pid[8];

	if (send_container(pid))
		return (1);
	pid_to_str(getpid(), client_pid);
	i = 0;
	c = 0;
	while (1)
	{
		if (send_sig(&client_pid[i], pid))
			return (1);
		c += 1;
		if (c == 8)
		{
			c = 0;
			i += 1;
			if (!client_pid[i])
				break ;
		}
	}
	if (send_container(pid))
		return (1);
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
	signal(SIGUSR1, acknowledgement);
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
			{
				if (send_client_pid(pid))
					return (1);
				return (0);
			}
		}
	}
}
