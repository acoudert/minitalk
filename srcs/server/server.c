#include "server.h"

void	clean(wchar_t *character, int *received_bits)
{
	*character = 0;
	*received_bits = 0;
}

void	sig_handler(int signum)
{
	static wchar_t		character = 0;
	static int			received_bits = 0;

	received_bits += 1;
	character <<= 1;
	if (signum == SIGUSR1)
		character += 1;
	if (received_bits == 8)
	{
		write(STDOUT_FILENO, &character, 1);
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
