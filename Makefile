NAME 		= philo
FLAGS		= -Wall -Wextra -Werror
CFLAGS		= $(FLAGS) -I. -g
CC			= gcc

ifeq ($(MAKECMDGOALS),bonus)
	OBJS = $(SRCS_BONUS:%.c=%.o)
else
	OBJS = $(SRCS:%.c=%.o)
endif

SRCS 		= src/philo.c \
			src/utils.c \
			src/philo_actions.c
SRCS_BONUS	=
INCLUDE		= philo.h

.PHONY: all clean fclean re bonus norm

.o: .c $(INCLUDE)
	$(CC) $(CFLAGS) $< -o $@

all: $(NAME)

${NAME}: $(OBJS) $(INCLUDE)
	$(CC) $(OBJS) -o $(NAME)

bonus: libft $(NAME)

norm:
	norminette $(SRCS)
	norminette $(SRCS_BONUS)
	norminette $(INCLUDE)
	make -C libft/ norm

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)
	rm -rf a.out*
	rm -rf */a.out*
	rm -rf *.gch
	rm -rf */*.gch

re: fclean all
