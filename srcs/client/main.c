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

void	pid_to_str(int n, char *pid)
{
	int		tmp;
	int		c;

	c = 0;
	tmp = n;
	while (tmp)
	{
		c += 1;
		tmp /= 10;
	}
	pid[c] = 0;
	while (n)
	{
		c -= 1;
		pid[c] = n % 10 + '0';
		n /= 10;
	}
}

void	send_client_pid(int pid)
{
	int		i;
	int		c;
	char	client_pid[8];

	i = 0;
	printf("ACK\n");
	while (i < 8)
	{
		printf("1");
		if (kill(pid, SIGUSR1) < 0)
			return ;
		i += 1;
		usleep(10000);
	}
	printf("\n");
	pid_to_str(getpid(), client_pid);
	i = 0;
	c = 0;
	printf("client_pid = %d\n", getpid());
	printf("server_pid = %d\n", pid);
	while (1)
	{
		//printf("client_pid = %s && i = %d && c = %d\n", client_pid + i, i, c);
		if (client_pid[i] & 128)
		{
			printf("1");
			if (kill(pid, SIGUSR1) < 0)
			{
				printf("Error\n");
				return ;
			}
		}
		else
		{
			printf("0");
			if (kill(pid, SIGUSR2) < 0)
			{
				printf("Error\n");
				return ;
			}
		}
		client_pid[i] <<= 1;
		c += 1;
		usleep(10000);
		if (c == 8)
		{
			c = 0;
			i += 1;
			if (!client_pid[i])
				break ;
			printf(" ");
		}
	}
	printf("\n");
	i = 0;
	while (i < 8)
	{
		printf("1");
		if (kill(pid, SIGUSR1) < 0)
			return ;
		i += 1;
		usleep(10000);
	}
	printf("\n");
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
			printf("1");
			if (kill(pid, SIGUSR1) < 0)
				return (4);
		}
		else
		{
			printf("0");
			if (kill(pid, SIGUSR2) < 0)
				return (4);
		}
		av[2][0] <<= 1;
		i += 1;
		usleep(10000);
		if (i == 8)
		{
			i = 0;
			av[2] = av[2] + 1;
			if (!av[2][0])
			{
				printf("\n");
				send_client_pid(pid);
				return (0);
			}
			printf(" ");
		}
	}
	return (1);
}
