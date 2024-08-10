NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -pthread

CFILES = main.c init.c utils.c parse.c\
		threads.c tasks.c actions.c \

OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
	@rm -f $(OBJECTS)


fclean: clean
	@rm -f $(NAME)


re: fclean all

norm:
	norminette

#run:	all

.PHONY: all clean fclean re norm