#include "server.h"

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
		*character ^= 917504;
	else if (*character >= 62914560)
		*character ^= 62914560;
}

int	handle_acknowledgement(wchar_t *character, int *received_bits
		, char *ack, int *client_pid)
{
	if (!*ack && *character == 255)
	{
		*ack = 1;
		clean(character, received_bits);
		return (1);
	}	
	else if (*ack && *character == 255)
	{
		printf("\nSending acknowledgement\n");
		clean(character, received_bits);
		kill(*client_pid, SIGUSR1);
		*ack = 0;
		*client_pid = 0;
		return (1);
	}
	if (*ack && *character != 255)
	{
		*client_pid *= 10;
		*client_pid += *character - '0';
		clean(character, received_bits);
		return (1);
	}
	return (0);
}

void	sig_handler(int signum)
{
	static wchar_t		character = 0;
	static int			received_bits = 0;
	static char			ack = 0;
	static int			client_pid = 0;

	received_bits += 1;
	character <<= 1;
	if (signum == SIGUSR1)
		character += 1;
	if (received_bits > 8 && (received_bits % 8 == 1 || received_bits % 8 == 2))
		character >>= 1;
	if ((received_bits == 8 && character <= 127)
		|| (received_bits == 8 && character == 255)
		|| (received_bits == 16 && character >= 12288 && character < 14336)
		|| (received_bits == 24 && character >= 917504 && character < 983040)
		|| (received_bits == 32))
	{
		if (handle_acknowledgement(&character, &received_bits
				, &ack, &client_pid))
			return ;
		update_character_value(&character);
		printf("%lc", character);
		clean(&character, &received_bits);
	}
}

int	main(void)
{
	char	pid[8];

	pid_to_str(getpid(), pid);
	write(STDOUT_FILENO, pid, ft_strlen(pid));
	write(STDOUT_FILENO, "\n", 1);
	setlocale(LC_CTYPE, "UTF-8");
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		pause();
	return (0);
}
