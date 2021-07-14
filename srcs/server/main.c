#include "server.h"

int		ft_strlen(char const *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

void	clean(wchar_t *character, int *received_bits)
{
	*character = 0;
	*received_bits = 0;
}

void	update_character_value(wchar_t *character)
{
	if (*character >= 12288 && *character < 14336)
		*character ^= 12288;
	else if (*character >= 917504 && *character < 983040)
		*character ^= 918504;
	else if (*character >= 62914560)
		*character ^= 62914560;
}

void	sig_handler(int signum)
{
	static wchar_t		character = 0;
	static int			received_bits = 0;

	received_bits += 1;
	character <<= 1;
	if (signum == SIGUSR1)
	{
		printf("1");
		character += 1;
	} else {
		printf("0");
	}
	if (received_bits % 8 == 0)
		printf(" ");
	if (received_bits > 8 && (received_bits % 8 == 1 || received_bits % 8 == 2))
	{
		character >>= 1;
	}
	if ((received_bits == 8 && character <= 127)
			|| (received_bits == 16 && character >= 12288 && character < 14336)
			|| (received_bits == 24 && character >= 917504 && character < 983040)
			|| (received_bits == 32))
	{
		printf("val = %d\n", character);
		update_character_value(&character);
		printf("%lc\n", character);
		clean(&character, &received_bits);
	}
}

int		main()
{
	char	pid[8];

	pid_to_str(getpid(), pid);
	write(STDOUT_FILENO, pid, ft_strlen(pid));
	write(STDOUT_FILENO,"\n", 1);
	setlocale(LC_CTYPE, "UTF-8");
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		pause();
	return (0);
}
