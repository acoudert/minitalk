#include "client.h"

int		ft_atoi(const char *nptr)
{
	int		nb;
	int		sign;

	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	sign = 1;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	nb = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nb *= 10;
		nb += *nptr - '0';
		nptr++;
	}
	return (sign * nb);
}

int		main(int ac, char **av)
{
	int		i;
	int		pid;

	if (ac != 3)
		return (1);
	pid = ft_atoi(av[1]);
	i = 0;
	while (av[2])
	{
		if (av[2][0] & 128)
		{
			if (kill(pid, SIGUSR1) < 0)
				return (4);
		}
		else
		{
			if (kill(pid, SIGUSR2) < 0)
				return (4);
		}
		av[2][0] <<= 1;
		i += 1;
		if (i == 8)
		{
			i = 0;
			av[2] = av[2] + 1;
			if (!av[2][0])
				return (0);
		}
		usleep(10000);
	}
	return (1);
}
