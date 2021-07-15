NAME1      = server
NAME1_BONUS = server_bonus
NAME2      = client
NAME2_BONUS = client_bonus

CC         = gcc
CINCLUDES  = -I includes
CFLAGS     = -Wall -Wextra -Werror $(CINCLUDES)
RM         = rm -f

DIR1       = srcs/server
DIR2       = srcs/client
DIR_UTILS  = srcs/utils

SRCS1      = $(DIR1)/server.c
SRCS1_BONUS = $(DIR1)/server_bonus.c
SRCS2      = $(DIR2)/client.c
SRCS2_BONUS = $(DIR2)/client_bonus.c
SRCS_UTILS = $(DIR_UTILS)/ft_atoi.c \
			 $(DIR_UTILS)/ft_strlen.c \
			 $(DIR_UTILS)/pid_to_str.c

OBJS1      = $(SRCS1:.c=.o)
OBJS1_BONUS = $(SRCS1_BONUS:.c=.o)
OBJS2      = $(SRCS2:.c=.o)
OBJS2_BONUS = $(SRCS2_BONUS:.c=.o)
OBJS_UTILS = $(SRCS_UTILS:.c=.o)

all        : $(NAME1) $(NAME2)

bonus        : $(NAME1_BONUS) $(NAME2_BONUS)

$(NAME1)   : $(OBJS1) $(OBJS_UTILS)
	$(CC) $^ -o $@ 

$(NAME1_BONUS)   : $(OBJS1_BONUS) $(OBJS_UTILS)
	$(CC) $^ -o $@ 

$(NAME2)   : $(OBJS2) $(OBJS_UTILS)
	$(CC) $^ -o $@

$(NAME2_BONUS)   : $(OBJS2_BONUS) $(OBJS_UTILS)
	$(CC) $^ -o $@

$(OBJS1)   : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS1_BONUS) : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS2)   : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS2_BONUS) : %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_UTILS): %.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

re         : fclean all

clean      :
	$(RM) $(OBJS1) $(OBJS2) $(OBJS1_BONUS) $(OBJS2_BONUS) $(OBJS_UTILS)

fclean     : clean
	$(RM) $(NAME1) $(NAME2) $(NAME1_BONUS) $(NAME2_BONUS)

.PHONY     : all bonus re clean fclean

