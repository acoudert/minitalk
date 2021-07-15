#ifndef CLIENT_H
# define CLIENT_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

# include <stdio.h>
# include <wchar.h>
# include <locale.h>

# include "utils.h"

# define TIME	100

char	send_sig(char *c, int pid);

#endif
