#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

# include <stdio.h>
# include <wchar.h>
# include <locale.h>

int		ft_atoi(const char *nptr);
int		ft_strlen(const char *str);
void	pid_to_str(int n, char *pid);

#endif
