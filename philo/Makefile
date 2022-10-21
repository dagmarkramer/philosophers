NAME		= philo
OBJ			= main libft_functions libft_functions2 philo_forks philo_threads philo_utils 
OBJS		= $(addsuffix .o, ${OBJ})
CC			= gcc
RM			= rm -f
HEADER		= -I philosophers.h
CFLAGS		= -Wall -Wextra -Werror

all:		${NAME}

obj/%.o:	src/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) $(RL_I) $(HEADER) -c -o $@ $<

clean:
				@${RM} ${OBJS} \
				$(info ************  philosophers Clean)

fclean:		clean
				@${RM} ${NAME}
				$(info ************  philosopers Removed)

re:			fclean all

${NAME}:	${OBJS}
				@${CC} $(OBJS) $(CFLAGS) -o $@
				$(info ************  philosophers Ready!)

.PHONY: all clean fclean re cleanft
