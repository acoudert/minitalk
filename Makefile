NAME1      = server
NAME2      = client

CC         = gcc
CINCLUDES  = -I includes
#CFLAGS     = -Wall -Wextra -Werror $(CINCLUDES)
CFLAGS     = $(CINCLUDES)
RM         = rm -f

DIR1       = srcs/server
DIR2       = srcs/client

SRCS1      = $(DIR1)/main.c
SRCS2      = $(DIR2)/main.c

OBJS1      = $(SRCS1:.c=.o)
OBJS2      = $(SRCS2:.c=.o)

all        : $(NAME1) $(NAME2)

$(NAME1)   : $(OBJS1)
	$(CC) $^ -o $@ 

$(NAME2)   : $(OBJS2)
	$(CC) $^ -o $@

$(OBJS1)   : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS2)   : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

re         : fclean all

clean      :
	$(RM) $(OBJS1) $(OBJS2)

fclean     : clean
	$(RM) $(NAME1) $(NAME2)

.PHONY     : all re clean fclean

